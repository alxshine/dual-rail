#include <iostream>
#include <unordered_set>

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

  unsigned int balanceValue(unsigned char v) {
    unsigned char inverse = ~v;
    return inverse << 16 | v;
  }

  Function *loadWithError(Module &M, string func_name) {
    auto *func = M.getFunction(func_name);
    if (func == nullptr)
      errs() << "Could not load function " << func_name << "\n";
    return func;
  }

  struct arithmetic_ret {
    Function *balance, *balance_wide, *unbalance;
    Function *op_or, *op_and, *op_xor, *op_add, *op_sub, *op_mul, *op_sdiv,
        *op_udiv, *op_srem, *op_urem, *op_shl, *op_ashr;
  };

  arithmetic_ret loadArithmetic(Module &M) {
    // get function pointers
    auto *balance_func = loadWithError(M, "balanced_int");
    auto *balance_func_wide = loadWithError(M, "balanced_int_wide");
    auto *unbalance_func = loadWithError(M, "unbalanced_int");

    auto *balanced_or = loadWithError(M, "balanced_or");
    auto *balanced_and = loadWithError(M, "balanced_and");
    auto *balanced_xor = loadWithError(M, "balanced_xor");
    auto *balanced_add = loadWithError(M, "balanced_add");
    auto *balanced_sub = loadWithError(M, "balanced_sub");
    auto *balanced_mul = loadWithError(M, "balanced_mul");
    auto *balanced_sdiv = loadWithError(M, "balanced_sdiv");
    auto *balanced_udiv = loadWithError(M, "balanced_udiv");
    auto *balanced_srem = loadWithError(M, "balanced_srem");
    auto *balanced_urem = loadWithError(M, "balanced_urem");
    auto *balanced_shl = loadWithError(M, "balanced_shl");
    auto *balanced_ashr = loadWithError(M, "balanced_ashr");

    arithmetic_ret ret;
    ret.balance = balance_func;
    ret.balance_wide = balance_func_wide;
    ret.unbalance = unbalance_func;

    ret.op_or = balanced_or;
    ret.op_and = balanced_and;
    ret.op_xor = balanced_xor;
    ret.op_add = balanced_add;
    ret.op_sub = balanced_sub;
    ret.op_mul = balanced_mul;
    ret.op_sdiv = balanced_sdiv;
    ret.op_udiv = balanced_udiv;
    ret.op_srem = balanced_urem;
    ret.op_shl = balanced_shl;
    ret.op_ashr = balanced_ashr;

    return ret;
  }

  struct clone_ret {
    vector<Function *> old_functions;
    vector<Function *> new_functions;
  };

  clone_ret cloneFunctions(Module &M) {
    vector<Function *> copied_functions;
    vector<Function *> old_functions;
    auto &context = M.getContext();

    // clone functions
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
      old_functions.push_back(&*F);
    }

    for (auto *F : copied_functions) {
      errs() << "Inserting new function " << F->getName() << "\n";
      M.getFunctionList().push_back(F);
    }

    return {old_functions, copied_functions};
  }

  void balanceGlobals(Module &M, unordered_set<Value *> &balanced_values) {
    auto &context = M.getContext();

    for (auto &global : M.getGlobalList()) {
      errs() << "Balancing global " << global.getName() << "\n";
      if (global.getValueType() == Type::getInt8Ty(context)) {
        auto name = "balanced_" + global.getName();

        Constant *initializer = nullptr;
        if (global.hasInitializer()) {
          auto *old_initializer = global.getInitializer();
          unsigned char v =
              old_initializer->getUniqueInteger().getLimitedValue(0xff);
          unsigned balanced_v = balanceValue(v);
          initializer =
              ConstantInt::get(Type::getInt32Ty(context), balanced_v, false);
        }

        auto *new_global = new GlobalVariable(
            M, Type::getInt32Ty(context), global.isConstant(),
            global.getLinkage(), initializer, name);
        global.replaceAllUsesWith(new_global);
        balanced_values.insert(new_global);
        errs() << global.getNumUses() << " uses remaining\n";
      }
    }
  }

  int balanceAlloca(AllocaInst *alloca, IRBuilder<> builder,
                    arithmetic_ret arithmetic, vector<Instruction *> &to_remove,
                    unordered_set<Value *> &balanced_values) {
    if (alloca->getAllocatedType() == builder.getInt8Ty()) {
      auto *new_alloc = builder.CreateAlloca(builder.getInt32Ty());
      alloca->replaceAllUsesWith(new_alloc);
      balanced_values.insert(new_alloc);
      to_remove.push_back(alloca);
      return 1;
    }
    return 0;
  }

  int balanceStore(StoreInst *store, IRBuilder<> builder,
                   arithmetic_ret arithmetic, vector<Instruction *> &to_remove,
                   unordered_set<Value *> &balanced_values) {
    auto *constant = dyn_cast<ConstantInt>(store->getValueOperand());
    if (constant && balanced_values.count(store->getPointerOperand())) {
      auto *new_const = builder.getInt8(constant->getLimitedValue());
      auto *balanced_const =
          builder.CreateCall(arithmetic.balance, {new_const});

      auto *new_store =
          builder.CreateStore(balanced_const, store->getPointerOperand());
      balanced_values.insert(new_store);
      to_remove.push_back(store);
      return 1;
    }

    auto *value = store->getValueOperand();
    auto *value_type = value->getType();
    auto *pointer = store->getPointerOperand();
    PointerType *pointer_type = (PointerType *)store->getPointerOperandType();
    auto *target_type = pointer_type->getElementType();

    if (value_type == builder.getInt8Ty() &&
        target_type == builder.getInt32Ty()) {

    } else if (value_type == builder.getInt32Ty() &&
               target_type == builder.getInt8Ty()) {
    }

    if (value_type == builder.getInt8Ty() &&
        target_type == builder.getInt32Ty()) {
      auto *balanced_val = builder.CreateCall(arithmetic.balance, {value});
      auto *new_store =
          builder.CreateStore(balanced_val, store->getPointerOperand());
      store->replaceAllUsesWith(new_store);
      to_remove.push_back(store);
    } else if (value_type == builder.getInt32Ty() &&
               target_type == builder.getInt8Ty()) {
      auto *unbalanced_val = builder.CreateCall(arithmetic.unbalance, {value});
      auto *new_store =
          builder.CreateStore(unbalanced_val, store->getPointerOperand());
      store->replaceAllUsesWith(new_store);
      to_remove.push_back(store);
    }
    return 1;
  }

  int balanceLoad(LoadInst *load, IRBuilder<> builder, arithmetic_ret,
                  vector<Instruction *> &to_remove,
                  unordered_set<Value *> &balanced_values) {
    if (balanced_values.count(load->getPointerOperand())) {
      auto *new_load = builder.CreateLoad(load->getPointerOperand());
      load->replaceAllUsesWith(new_load);
      balanced_values.insert(new_load);
      to_remove.push_back(load);
      return 1;
    }
    return 0;
  }

  int balanceZExt(ZExtInst *zext, IRBuilder<> builder,
                  arithmetic_ret arithmetic, vector<Instruction *> &to_remove,
                  unordered_set<Value *> &balanced_values) {
    if (zext->getSrcTy() == zext->getDestTy()) {
      zext->replaceAllUsesWith(zext->getOperand(0));
      to_remove.push_back(zext);
      return 1;
    }

    // if we zext from i8 to i32, balance instead
    if (zext->getSrcTy() == builder.getInt8Ty() &&
        zext->getDestTy() == builder.getInt32Ty()) {
      auto *balance_call =
          builder.CreateCall(arithmetic.balance, {zext->getOperand(0)});
      zext->replaceAllUsesWith(balance_call);
      balanced_values.insert(balance_call);
      to_remove.push_back(zext);
      return 1;
    }

    // llvm doesn't zext from i8 to i64 directly, so any zext starting
    // from a balanced value must first unbalance
    if (balanced_values.count(zext->getOperand(0))) {
      auto *balanced_val = zext->getOperand(0);
      auto *unbalanced_val =
          builder.CreateCall(arithmetic.unbalance, {balanced_val});
      auto *first_zext =
          builder.CreateZExt(unbalanced_val, balanced_val->getType());
      auto *final_zext = builder.CreateZExt(first_zext, zext->getDestTy());
      zext->replaceAllUsesWith(final_zext);
      to_remove.push_back(zext);
      return 1;
    }

    return 0;
  }

  int balanceOp(BinaryOperator *op, IRBuilder<> builder,
                arithmetic_ret arithmetic, vector<Instruction *> &to_remove,
                unordered_set<Value *> &balanced_values) {
    // check for balancedness of all operators
    auto *op1 = op->getOperand(0);
    bool balanced1 = balanced_values.count(op1);
    bool constant1 = isa<ConstantInt>(op1);
    auto *op2 = op->getOperand(1);
    bool balanced2 = balanced_values.count(op2);
    bool constant2 = isa<ConstantInt>(op2);

    bool correct = true;
    if (balanced1)
      correct = balanced2 || constant2;
    else if (balanced2)
      correct = constant1;

    if (!correct) {
      errs() << "found broken binary operation, only partially balanced\n";
      op->print(errs());
      errs() << "\n";
      op1->print(errs());
      errs() << ", ";
      op2->print(errs());
      errs() << "\n";
      return 1;
    }
    // if nothing is balanced, there is nothing to do here
    if (!balanced1 && !balanced2)
      return 1;

    // fix constants in binary operations
    Value *operands[2] = {op->getOperand(0), op->getOperand(1)};
    for (int i = 0; i < 2; i++) {
      auto *constant =
          dyn_cast<ConstantInt>(op->getOperand(i)); // TODO: next step

      if (constant) {
        Value *balanced_constant;
        if (constant->getType() == builder.getInt8Ty())
          balanced_constant =
              builder.CreateCall(arithmetic.balance, {constant});
        else if (constant->getType() == builder.getInt32Ty())
          balanced_constant =
              builder.CreateCall(arithmetic.balance_wide, {constant});
        else {
          errs() << "Could not balance constant of type ";
          constant->getType()->print(errs());
          errs() << "\n";
        }

        operands[i] = balanced_constant;
        balanced_values.insert(balanced_constant);
      }
    }

    // change operations to balanced operations
    auto opcode = op->getOpcode();

    Value *call;
    if (opcode == llvm::Instruction::BinaryOps::Or)
      call = builder.CreateCall(arithmetic.op_or, operands);
    else if (opcode == llvm::Instruction::BinaryOps::And)
      call = builder.CreateCall(arithmetic.op_and, operands);
    else if (opcode == llvm::Instruction::BinaryOps::Xor)
      call = builder.CreateCall(arithmetic.op_xor, operands);
    else if (opcode == llvm::Instruction::BinaryOps::Add)
      call = builder.CreateCall(arithmetic.op_add, operands);
    else if (opcode == llvm::Instruction::BinaryOps::Sub)
      call = builder.CreateCall(arithmetic.op_sub, operands);
    else if (opcode == llvm::Instruction::BinaryOps::Mul)
      call = builder.CreateCall(arithmetic.op_mul, operands);
    else if (opcode == llvm::Instruction::BinaryOps::SDiv)
      call = builder.CreateCall(arithmetic.op_sdiv, operands);
    else if (opcode == llvm::Instruction::BinaryOps::UDiv)
      call = builder.CreateCall(arithmetic.op_udiv, operands);
    else if (opcode == llvm::Instruction::BinaryOps::SRem)
      call = builder.CreateCall(arithmetic.op_srem, operands);
    else if (opcode == llvm::Instruction::BinaryOps::URem)
      call = builder.CreateCall(arithmetic.op_urem, operands);
    else if (opcode == llvm::Instruction::BinaryOps::Shl)
      call = builder.CreateCall(arithmetic.op_shl, operands);
    else if (opcode == llvm::Instruction::BinaryOps::AShr)
      call = builder.CreateCall(arithmetic.op_ashr, operands);
    else {
      errs() << "No balanced variant found for operation "
             << op->getOpcodeName() << "\n";
      throw 4;
    }

    op->replaceAllUsesWith(call);
    balanced_values.insert(call);
    to_remove.push_back(op);
    return 1;
  }

  int balanceGetElementPtr(GetElementPtrInst *getelem, IRBuilder<> builder,
                           arithmetic_ret arithmetic,
                           vector<Instruction *> &to_remove,
                           unordered_set<Value *> &balanced_values) {
    int numops = getelem->getNumOperands();
    for (int i = 1; i < numops; ++i) {
      auto *op = getelem->getOperand(i);
      if (balanced_values.count(op)) {
        auto *unbalanced_val = builder.CreateCall(arithmetic.unbalance, {op});
        auto *extended_val =
            builder.CreateZExt(unbalanced_val, builder.getInt32Ty());
        getelem->setOperand(i, extended_val);
      }
    }
    return 1;
  }

  int balanceCmp(CmpInst *cmp, IRBuilder<> builder, arithmetic_ret arithmetic,
                 vector<Instruction *> &to_remove,
                 unordered_set<Value *> &balanced_values) {
    auto *op1 = cmp->getOperand(0);
    bool balanced1 = balanced_values.count(op1);
    bool constant1 = isa<ConstantInt>(op1);
    auto *op2 = cmp->getOperand(1);
    bool balanced2 = balanced_values.count(op2);
    bool constant2 = isa<ConstantInt>(op2);

    bool correct = true;
    if (balanced1)
      correct = balanced2 || constant2;
    else if (balanced2)
      correct = constant1;

    if (!correct) {
      errs() << "Found comparison between balanced and unbalanced value\n";
      return 1;
    }

    if (!balanced1 && !balanced2)
      return 1;

    if (constant1) {
      auto *constant = dyn_cast<ConstantInt>(op1);
      if (constant->getType() != builder.getInt8Ty())
        op1 = builder.CreateIntCast(constant, builder.getInt8Ty(), false);
      auto *balanced_constant = builder.CreateCall(arithmetic.balance, op1);
      op1 = balanced_constant;
    }

    if (constant2) {
      auto *constant = dyn_cast<ConstantInt>(op2);
      if (constant->getType() != builder.getInt8Ty())
        op2 = builder.CreateIntCast(constant, builder.getInt8Ty(), false);
      auto *balanced_constant = builder.CreateCall(arithmetic.balance, op2);
      op2 = balanced_constant;
    }

    // finally we need to change the comparison direction for lt and gt
    // because we now compare the balancing part (which is inverse)
    auto pred = cmp->getPredicate();
    if (pred == CmpInst::Predicate::ICMP_SLT ||
        pred == CmpInst::Predicate::ICMP_ULT)
      pred = CmpInst::Predicate::ICMP_UGT;
    else if (pred == CmpInst::Predicate::ICMP_SGT ||
             pred == CmpInst::Predicate::ICMP_UGT)
      pred = CmpInst::Predicate::ICMP_ULT;

    auto *new_compare = builder.CreateICmp(pred, op1, op2);
    cmp->replaceAllUsesWith(new_compare);
    to_remove.push_back(cmp);
    balanced_values.insert(new_compare);
    return 1;
  }

  void balanceFunction(Function *F, arithmetic_ret arithmetic,
                       unordered_set<Value *> &balanced_values) {
    errs() << "Balancing function " << F->getName() << "\n";
    vector<Instruction *> to_remove;

    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
      IRBuilder<> builder{&*I};

      // alloca i32 instead of i8
      if (auto alloca = dyn_cast<AllocaInst>(&*I)) {
        if (balanceAlloca(alloca, builder, arithmetic, to_remove,
                          balanced_values))
          continue;
      }

      // store i32 constants instead of i8
      if (auto *store = dyn_cast<StoreInst>(&*I)) {
        if (balanceStore(store, builder, arithmetic, to_remove,
                         balanced_values))
          continue;
      }

      // load i32 values instead of i8
      if (auto *load = dyn_cast<LoadInst>(&*I)) {
        if (balanceLoad(load, builder, arithmetic, to_remove, balanced_values))
          continue;
      }

      // remove unnecessary zexts
      if (auto *zext = dyn_cast<ZExtInst>(&*I)) {
        if (balanceZExt(zext, builder, arithmetic, to_remove, balanced_values))
          continue;
      }

      if (auto *op = dyn_cast<BinaryOperator>(&*I)) {
        if (balanceOp(op, builder, arithmetic, to_remove, balanced_values))
          continue;
      }

      // unbalance before usage as array index
      if (auto *getelem = dyn_cast<GetElementPtrInst>(&*I)) {
        if (balanceGetElementPtr(getelem, builder, arithmetic, to_remove,
                                 balanced_values))
          continue;
      }

      // balance cmp instructions
      if (auto cmp = dyn_cast<CmpInst>(&*I)) {
        balanceCmp(cmp, builder, arithmetic, to_remove, balanced_values);
      }

      // add cast before return if necessary
      if (auto ret = dyn_cast<ReturnInst>(&*I)) {
        if (ret->getNumOperands() > 0) {
          auto *operand = ret->getOperand(0);
          if (operand->getType() == builder.getInt8Ty() &&
              F->getReturnType() == builder.getInt32Ty()) {
            auto *balanced_val =
                builder.CreateCall(arithmetic.balance, {operand});
            auto *new_ret = builder.CreateRet(balanced_val);
            ret->replaceAllUsesWith(new_ret);
            to_remove.push_back(ret);
          }
        }
        continue;
      }

      // replace calls with calls to balanced functions
      if (auto call = dyn_cast<CallInst>(&*I)) {
        auto original_name = call->getCalledFunction()->getName();
        if (original_name.startswith_lower("balanced_") ||
            original_name.startswith_lower("unbalanced_"))
          continue;
        auto new_name = "balanced_" + original_name;
        SmallVector<char, 100> buffer;
        auto string_ref = new_name.toStringRef(buffer);
        auto new_function = F->getParent()->getFunction(string_ref);
        SmallVector<Value *, 4> args;
        for (int i = 0; i < call->getNumArgOperands(); i++) {
          auto *arg = call->getArgOperand(i);
          if (arg->getType() == builder.getInt8Ty()) {
            auto *balanced_val = builder.CreateCall(arithmetic.balance, {arg});
            args.push_back(balanced_val);
          } else {
            args.push_back(arg);
          }
        }

        auto *new_call = builder.CreateCall(new_function->getFunctionType(),
                                            new_function, args);

        call->replaceAllUsesWith(new_call);
        balanced_values.insert(new_call);
        to_remove.push_back(call);
        continue;
      }
    }

    for (auto *I : to_remove) {
      I->eraseFromParent();
    }
  }

  virtual bool runOnModule(Module &M) {
    errs() << "Running on module: " << M.getName() << "\n";
    ModuleSlotTracker MST(&M, true);

    auto &context = M.getContext();
    unordered_set<Value *> balanced_values{};

    auto clone_ret = cloneFunctions(M);
    auto &copied_functions = clone_ret.new_functions;
    auto &old_functions = clone_ret.old_functions;

    auto arithmetic = loadArithmetic(M);

    balanceGlobals(M, balanced_values);

    for (auto *F : copied_functions) {
      balanceFunction(F, arithmetic, balanced_values);
    }

    for (auto *F : old_functions) {
      F->replaceAllUsesWith(UndefValue::get(F->getType()));
      F->eraseFromParent();
    }

    // remove dead functions
    bool has_changed = true;
    while (has_changed) {
      has_changed = false;
      vector<Function *> remove;
      for (auto F = M.begin(); F != M.end(); ++F) {
        if (F->getName() == "balanced_c_entry")
          continue;
        if (F->getNumUses() == 0) {
          remove.push_back(&*F);
          has_changed = true;
        }
      }
      for (auto *F : remove)
        F->eraseFromParent();
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
