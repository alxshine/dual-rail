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
        argumentTypes.push_back(arg->getType());
      }
      auto *funcType =
          FunctionType::get(F->getReturnType(), argumentTypes, false);
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
          }
        }

        // store i32 constants instead of i8
        if (auto store = dyn_cast<StoreInst>(&*I)) {
          auto *constant = dyn_cast<ConstantInt>(store->getValueOperand());
          if (constant && constant->getType() == Type::getInt8Ty(context) &&
              store->getPointerOperandType() == Type::getInt32PtrTy(context)) {
            auto const_value = constant->getLimitedValue();
            auto *new_const =
                ConstantInt::getSigned(Type::getInt32Ty(context), const_value);

            auto *new_store =
                new StoreInst(new_const, store->getPointerOperand(), store);
            to_remove.push_back(store);
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
        }
      }

      for (auto *I : to_remove) {
        I->eraseFromParent();
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
