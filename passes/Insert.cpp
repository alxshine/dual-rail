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
    vector<Function *> copiedFunctions;

    auto &context = M.getContext();
    vector<pair<unsigned, Attribute>> attributes{
        {1, Attribute::get(context, Attribute::AttrKind::NoInline)},
        {2, Attribute::get(context, Attribute::AttrKind::NoUnwind)},
    };
    auto attributeList = AttributeList::get(context, attributes);

    // copy the functions
    for (auto F = M.begin(); F != M.end(); ++F) {
      std::vector<Type *> argumentTypes;
      for (auto arg = F->arg_begin(); arg != F->arg_end(); ++arg) {
        argumentTypes.push_back(arg->getType());
      }
      auto *funcType =
          FunctionType::get(Type::getInt8Ty(context), argumentTypes, false);
      auto *newFunc = Function::Create(funcType, F->getLinkage());
      string oldName = F->getName();
      string newName = "balanced_" + oldName;
      newFunc->setName(newName);
      newFunc->setAttributes(attributeList);

      auto *newBlock = BasicBlock::Create(context, "dummy", newFunc);
      IRBuilder<> builder(newBlock);
      auto alloc = builder.CreateAlloca(builder.getInt32Ty(),
                                        newFunc->getAddressSpace());
      builder.CreateRet(builder.getInt8(1));

      // newFunc->getBasicBlockList().splice(newFunc->begin(),
      //                                     F->getBasicBlockList());

      copiedFunctions.push_back(newFunc);
    }

    for (auto *F : copiedFunctions) {
      errs() << "Inserting new function " << F->getName() << "\n";
      M.getFunctionList().push_back(F);
      if (F->getName() == "balanced_c_entry") {
        F->print(errs());
        errs() << "\n";
      }
    }

    return copiedFunctions.size();
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
