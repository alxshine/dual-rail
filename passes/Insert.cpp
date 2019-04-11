#include <iostream>

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/ModuleSlotTracker.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
using namespace llvm;
using namespace std;

namespace {
struct SkeletonPass : public ModulePass {
  static char ID;
  SkeletonPass() : ModulePass(ID) {}

  virtual bool runOnModule(Module &M) {
    errs() << "Running on module: " << M.getName() << "\n";
    ModuleSlotTracker MST(&M, true);
    vector<Function *> copied_functions;

    auto &context = M.getContext();

    // copy the functions
    for (auto F = M.begin(); F != M.end(); ++F) {
      // create cloned function
      std::vector<Type *> argumentTypes;
      for (auto arg = F->arg_begin(); arg != F->arg_end(); ++arg) {
        auto *arg_type = arg->getType();
        if (arg_type == Type::getInt8Ty(context))
          arg_type = Type::getInt32Ty(context);

        argumentTypes.push_back(arg_type);
      }

      auto *return_type = F->getReturnType();
      if (return_type == Type::getInt8Ty(context))
        return_type = Type::getInt32Ty(context);

      auto *funcType = FunctionType::get(return_type, argumentTypes, false);
      auto *newFunc = Function::Create(funcType, F->getLinkage());
      string oldName = F->getName();
      string newName = "balanced_" + oldName;
      newFunc->setName(newName);
      newFunc->setAttributes(F->getAttributes());

      // create value mapping
      ValueToValueMapTy vMap;
      for (auto arg = F->arg_begin(), new_arg = newFunc->arg_begin();
           arg != F->arg_end(); ++arg, ++new_arg) {
        vMap[&*arg] = &*new_arg;
      }

      // clone actual function
      SmallVector<ReturnInst *, 8> returns;
      CloneFunctionInto(newFunc, &*F, vMap, false, returns, "", nullptr,
                        nullptr, nullptr);

      copied_functions.push_back(newFunc);
    }

    for (auto *F : copied_functions) {
      errs() << "Inserting new function " << F->getName() << "\n";
      M.getFunctionList().push_back(F);
    }

    for (auto *F : copied_functions) {
      vector<Instruction *> to_remove;
      for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
        // alloca i32 instead of i8
        if (auto alloca = dyn_cast<AllocaInst>(&*I)) {
          if (alloca->getAllocatedType() == Type::getInt8Ty(context)) {
            // TODO: maybe use setAllocatedType here?
            auto *new_alloc =
                new AllocaInst(Type::getInt32Ty(context), F->getAddressSpace(),
                               nullptr, "", alloca);
            alloca->replaceAllUsesWith(new_alloc);
            to_remove.push_back(alloca);
            continue;
          }
        }

        // store i32 constants instead of i8
        if (auto *store = dyn_cast<StoreInst>(&*I)) {
          auto *constant = dyn_cast<ConstantInt>(store->getValueOperand());
          if (constant && constant->getType() == Type::getInt8Ty(context) &&
              store->getPointerOperandType() == Type::getInt32PtrTy(context)) {
            auto const_value = constant->getLimitedValue();
            auto *new_const =
                ConstantInt::getSigned(Type::getInt32Ty(context), const_value);

            auto *new_store =
                new StoreInst(new_const, store->getPointerOperand(), store);
            to_remove.push_back(store);
            continue;
          }
        }

        // load i32 values instead of i8
        if (auto *load = dyn_cast<LoadInst>(&*I)) {
          if (load->getType() == Type::getInt8Ty(context) &&
              load->getPointerOperandType() == Type::getInt32PtrTy(context)) {
            auto *new_load = new LoadInst(load->getPointerOperand(), "", load);
            load->replaceAllUsesWith(new_load);
            to_remove.push_back(load);
            continue;
          }
        }

        // remove unnecessary zexts
        if (auto *zext = dyn_cast<ZExtInst>(&*I)) {
          if (zext->getSrcTy() == zext->getDestTy()) {
            zext->replaceAllUsesWith(zext->getOperand(0));
            to_remove.push_back(zext);
            continue;
          }
        }

        // fix constants in binary operations
        if (auto *op = dyn_cast<BinaryOperator>(&*I)) {
          if (op->getOperand(0)->getType() == Type::getInt32Ty(context) ||
              op->getOperand(0)->getType() == Type::getInt32Ty(context)) {
            Value *operands[2] = {op->getOperand(0), op->getOperand(1)};
            for (int i = 0; i < 2; i++) {
              auto *constant = dyn_cast<ConstantInt>(op->getOperand(i));
              if (constant &&
                  constant->getType() != Type::getInt32Ty(context)) {
                auto *new_constant = ConstantInt::getSigned(
                    Type::getInt32Ty(context), constant->getLimitedValue());
                operands[i] = new_constant;
              }
            }
            auto *new_op = BinaryOperator::Create(op->getOpcode(), operands[0],
                                                  operands[1], Twine(), op);
            op->replaceAllUsesWith(new_op);
            to_remove.push_back(op);
            continue;
          }
        }

        // fix stores of different types
        if (auto *store = dyn_cast<StoreInst>(&*I)) {
          auto *value_type = store->getValueOperand()->getType();
          PointerType *pointer_type =
              (PointerType *)store->getPointerOperandType();
          auto *target_type = pointer_type->getElementType();

          if (value_type != target_type) {
            IRBuilder<> builder(store);
            auto *cast = builder.CreateIntCast(store->getValueOperand(),
                                               target_type, false);
            auto *new_store =
                builder.CreateStore(cast, store->getPointerOperand());
            store->replaceAllUsesWith(new_store);
            to_remove.push_back(store);
          }
        }

        // replace truncate with and TODO: test this for more general code
        if (auto truncate = dyn_cast<TruncInst>(&*I)) {
          if (truncate->getType() == Type::getInt8Ty(context)) {
            int mask = 0xff;
            IRBuilder<> builder(truncate);
            auto *constant = builder.getInt32(mask);
            auto *and_op = builder.CreateBinOp(
                Instruction::BinaryOps::And, truncate->getOperand(0), constant);
            truncate->replaceAllUsesWith(and_op);
            to_remove.push_back(truncate);
          }
        }

        // replace calls with calls to balanced functions
        if (auto call = dyn_cast<CallInst>(&*I)) {
          auto original_name = call->getCalledFunction()->getName();
          auto new_name = "balanced_" + original_name;
          SmallVector<char, 100> buffer;
          auto string_ref = new_name.toStringRef(buffer);
          auto new_function = M.getFunction(string_ref);
          call->setCalledFunction(new_function);
          IRBuilder<> builder(call);
          for (int i = 0; i < call->getNumOperands(); ++i) {
            auto *operand = call->getOperand(i);
            if (operand->getType() == builder.getInt8Ty()) {
              auto *cast =
                  builder.CreateIntCast(operand, builder.getInt32Ty(), true);
              call->setOperand(i, cast);
            }
          }
          continue;
        }
      }

      for (auto *I : to_remove) {
        I->eraseFromParent();
      }

      if (F->getName() == "balanced_xtime") {
        F->print(errs());
        errs() << "\n\n";
      }
    }

    return copied_functions.size();
  }
};
} // namespace

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerSkeletonPass);

static RegisterPass<SkeletonPass> X("insert", "Operator function insert pass",
                                    false, false);
