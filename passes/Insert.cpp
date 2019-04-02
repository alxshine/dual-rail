#include <iostream>

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;
using namespace std;

namespace {
struct SkeletonPass : public FunctionPass {
  static char ID;
  SkeletonPass() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) {
    // Get the function to call from our runtime library.
    LLVMContext &Ctx = F.getContext();

    errs() << "I saw a function called " << F.getName() << "!\n";

    std::vector<Type *> paramTypes = {Type::getInt32Ty(Ctx)};
    Type *retType = Type::getVoidTy(Ctx);
    FunctionType *logFuncType = FunctionType::get(retType, paramTypes, false);
    Constant *logFunc =
        F.getParent()->getOrInsertFunction("logop", logFuncType);

    for (auto &B : F) {   // for all blocks
      for (auto &I : B) { // for all instructions
        if (auto *op = dyn_cast<BinaryOperator>(&I)) {
          if (op->getType()->getIntegerBitWidth() != 32)
            continue;
          // Insert *after* `op`.
          // IRBuilder<> builder(op);
          // builder.SetInsertPoint(&B, ++builder.GetInsertPoint());

          // Insert a call to our function.
          // Value *args[] = {op};
          // builder.CreateCall(logFunc, args);

          return true;
        }
      }
    }

    return false;
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
