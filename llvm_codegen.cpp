#include "llvm_codegen.hpp"
#include <iostream>

LLVMCodeGen::LLVMCodeGen()
    : module("MyLLVMProgram", context), builder(context) {}

void LLVMCodeGen::generateCode(std::unique_ptr<ProgramNode>& ast) {
    std::cout << "Generating LLVM IR..." << std::endl;

    // Create main function
    llvm::FunctionType *funcType =
        llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function *mainFunction =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    // Create an entry block
    llvm::BasicBlock *entryBlock = llvm::BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entryBlock);

    // Process each statement in the AST
    for (const auto& stmt : ast->statements) {
        generateStatement(stmt.get());
    }

    // Return 0 from main
    builder.CreateRet(builder.getInt32(0));
}

void LLVMCodeGen::generateStatement(ASTNode* node) {
    if (auto* varAssign = dynamic_cast<VariableAssignmentNode*>(node)) {
        generateVariableAssignment(varAssign);
    } else if (auto* printStmt = dynamic_cast<PrintStatementNode*>(node)) {
        generatePrintStatement(printStmt);
    }
}

void LLVMCodeGen::generateVariableAssignment(VariableAssignmentNode* node) {
    llvm::AllocaInst* varAlloc = builder.CreateAlloca(llvm::Type::getInt32Ty(context), nullptr, node->variableName);
    llvm::Value* value = generateExpression(node->expression.get());
    builder.CreateStore(value, varAlloc);
    variables[node->variableName] = varAlloc; // Store pointer to variable
}


llvm::Value* LLVMCodeGen::generateExpression(ASTNode* node) {
    if (auto* integerNode = dynamic_cast<IntegerNode*>(node)) {
        return llvm::ConstantInt::get(context, llvm::APInt(32, integerNode->value));
    } else if (auto* identifierNode = dynamic_cast<IdentifierNode*>(node)) {
    llvm::Value* varPtr = variables[identifierNode->name];
    return builder.CreateLoad(llvm::Type::getInt32Ty(context), varPtr, identifierNode->name);
    } else if (auto* binaryExpr = dynamic_cast<BinaryExpressionNode*>(node)) {
        llvm::Value* left = generateExpression(binaryExpr->left.get());
        llvm::Value* right = generateExpression(binaryExpr->right.get());

        if (binaryExpr->op == "+") {
            return builder.CreateAdd(left, right, "addtmp");
        }
    }
    return nullptr;
}

void LLVMCodeGen::generatePrintStatement(PrintStatementNode* node) {
    llvm::Value* value = generateExpression(node->expression.get());

    llvm::Function* printfFunc = module.getFunction("printf");
    if (!printfFunc) {
        llvm::FunctionType *printfType = llvm::FunctionType::get(builder.getInt32Ty(), true);
        printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
    }

    llvm::Value* formatStr = builder.CreateGlobalStringPtr("%d\n");

    // ✅ Ensure only one load happens
    if (value->getType()->isPointerTy()) {
        value = builder.CreateLoad(llvm::Type::getInt32Ty(context), value, "printload");
    }

    builder.CreateCall(printfFunc, { formatStr, value });
}


void LLVMCodeGen::printLLVMIR() {
    module.print(llvm::outs(), nullptr);
}
