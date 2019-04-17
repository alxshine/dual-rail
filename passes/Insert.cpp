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

    // get function pointers
    auto *balance_func = M.getFunction("balanced_int");
    auto *const_balance_func = M.getFunction("balanced_constant");
    auto *unbalance_func = M.getFunction("unbalanced_int");

    auto *balanced_or = M.getFunction("balanced_or");
    auto *balanced_and = M.getFunction("balanced_and");
    auto *balanced_xor = M.getFunction("balanced_xor");
    auto *balanced_add = M.getFunction("balanced_add");
    auto *balanced_sub = M.getFunction("balanced_sub");
    auto *balanced_mul = M.getFunction("balanced_mul");
    auto *balanced_sdiv = M.getFunction("balanced_sdiv");
    auto *balanced_udiv = M.getFunction("balanced_udiv");
    auto *balanced_srem = M.getFunction("balanced_srem");
    auto *balanced_urem = M.getFunction("balanced_urem");
    auto *balanced_shl = M.getFunction("balanced_shl");
    auto *balanced_ashr = M.getFunction("balanced_ashr");

    // copy the functions
    for (auto F = M.begin(); F != M.end(); ++F) {
      auto name = F->getName();
      if (name.startswith_lower("balanced_") || name.startswith("unbalanced_"))
        continue;

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
            IRBuilder<> builder(store);
            auto *new_const = builder.getInt8(constant->getLimitedValue());
            auto *balanced_const =
                builder.CreateCall(balance_func, {new_const});

            auto *new_store =
                builder.CreateStore(balanced_const, store->getPointerOperand());
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

        if (auto *op = dyn_cast<BinaryOperator>(&*I)) {
          IRBuilder<> builder{op};

          // fix constants in binary operations
          if (op->getOperand(0)->getType() == Type::getInt32Ty(context) ||
              op->getOperand(0)->getType() == Type::getInt32Ty(context)) {
            Value *operands[2] = {op->getOperand(0), op->getOperand(1)};
            for (int i = 0; i < 2; i++) {
              auto *constant =
                  dyn_cast<ConstantInt>(op->getOperand(i)); // TODO: next step
              if (constant &&
                  constant->getType() != Type::getInt32Ty(context)) {
                auto old_int = constant->getUniqueInteger();
                APInt new_int{32, old_int.getLimitedValue()};
                if (old_int.isNegative())
                  new_int.setBitsFrom(8);
                auto *new_constant = builder.getInt(new_int);
                auto *balanced_constant =
                    builder.CreateCall(const_balance_func, {new_constant});

                operands[i] = balanced_constant;
              }
            }
            auto *new_op = BinaryOperator::Create(op->getOpcode(), operands[0],
                                                  operands[1], Twine(), op);
            op->replaceAllUsesWith(new_op);
            to_remove.push_back(op);
            op = new_op;
          }

          // change operations to balanced operations
          auto opcode = op->getOpcode();
          SmallVector<Value *, 2> operands;
          for (int i = 0; i < 2; ++i) {
            operands.push_back(op->getOperand(i));
          }

          Value *call;
          if (opcode == llvm::Instruction::BinaryOps::Or)
            call = builder.CreateCall(balanced_or, operands);
          else if (opcode == llvm::Instruction::BinaryOps::And)
            call = builder.CreateCall(balanced_and, operands);
          else if (opcode == llvm::Instruction::BinaryOps::Xor)
            call = builder.CreateCall(balanced_xor, operands);
          else if (opcode == llvm::Instruction::BinaryOps::Add)
            call = builder.CreateCall(balanced_add, operands);
          else if (opcode == llvm::Instruction::BinaryOps::Sub)
            call = builder.CreateCall(balanced_sub, operands);
          else if (opcode == llvm::Instruction::BinaryOps::Mul)
            call = builder.CreateCall(balanced_mul, operands);
          else if (opcode == llvm::Instruction::BinaryOps::SDiv)
            call = builder.CreateCall(balanced_sdiv, operands);
          else if (opcode == llvm::Instruction::BinaryOps::UDiv)
            call = builder.CreateCall(balanced_udiv, operands);
          else if (opcode == llvm::Instruction::BinaryOps::SRem)
            call = builder.CreateCall(balanced_srem, operands);
          else if (opcode == llvm::Instruction::BinaryOps::URem)
            call = builder.CreateCall(balanced_urem, operands);
          else if (opcode == llvm::Instruction::BinaryOps::Shl)
            call = builder.CreateCall(balanced_shl, operands);
          else if (opcode == llvm::Instruction::BinaryOps::AShr)
            call = builder.CreateCall(balanced_ashr, operands);
          else {
            errs() << "No balanced variant found for operation "
                   << op->getOpcodeName() << "\n";
            return -1;
          }
          op->replaceAllUsesWith(call);
          to_remove.push_back(op);
        }

        // fix stores of different types
        if (auto *store = dyn_cast<StoreInst>(&*I)) {
          auto *value = store->getValueOperand();
          auto *value_type = value->getType();
          auto *pointer = store->getPointerOperand();
          PointerType *pointer_type =
              (PointerType *)store->getPointerOperandType();
          auto *target_type = pointer_type->getElementType();

          IRBuilder<> builder(store);
          if (value_type == builder.getInt8Ty() &&
              target_type == builder.getInt32Ty()) {

          } else if (value_type == builder.getInt32Ty() &&
                     target_type == builder.getInt8Ty()) {
          }

          if (value_type !=
              target_type) { // TODO: this could cause some very hard to find
                             // bugs -> check for i8 and i32 specifically
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

        // add cast before return if necessary
        if (auto ret = dyn_cast<ReturnInst>(&*I)) {
          if (ret->getNumOperands() > 0) {
            auto *operand = ret->getOperand(0);
            if (operand->getType() == Type::getInt8Ty(context) &&
                F->getReturnType() == Type::getInt32Ty(context)) {
              IRBuilder<> builder(ret);
              auto *balanced_val = builder.CreateCall(balance_func, {operand});
              auto *new_ret = builder.CreateRet(balanced_val);
              ret->replaceAllUsesWith(new_ret);
              to_remove.push_back(ret);
            }
          }
        }

        // replace calls with calls to balanced functions
        if (auto call = dyn_cast<CallInst>(&*I)) {
          auto original_name = call->getCalledFunction()->getName();
          auto new_name = "balanced_" + original_name;
          SmallVector<char, 100> buffer;
          auto string_ref = new_name.toStringRef(buffer);
          auto new_function = M.getFunction(string_ref);
          IRBuilder<> builder(call);
          SmallVector<Value *, 4> args;
          for (int i = 0; i < call->getNumArgOperands(); i++) {
            auto *arg = call->getArgOperand(i);
            if (arg->getType() == builder.getInt8Ty()) {
              auto *balanced_val = builder.CreateCall(balance_func, {arg});
              args.push_back(balanced_val);
            } else {
              args.push_back(arg);
            }
          }

          auto *new_call = builder.CreateCall(new_function->getFunctionType(),
                                              new_function, args);

          call->replaceAllUsesWith(new_call);
          to_remove.push_back(call);
          continue;
        }
      }

      for (auto *I : to_remove) {
        I->eraseFromParent();
      }

      // if (F->getName() == "balanced_xtime") {
      //   F->print(errs());
      //   errs() << "\n";
      // }
    }

    return copied_functions.size();
  }
}; // namespace
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
