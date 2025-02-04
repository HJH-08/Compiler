#ifndef LLVM_CODEGEN_HPP
#define LLVM_CODEGEN_HPP

#include "ast.hpp"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <unordered_map>
#include <memory>

class LLVMCodeGen {
private:
    llvm::LLVMContext context;    // Stores LLVM global state
    llvm::Module module;          // Represents the whole program
    llvm::IRBuilder<> builder;    // Helps generate LLVM instructions

    std::unordered_map<std::string, llvm::Value*> variables;  // Symbol table

    void generateStatement(ASTNode* node);
    void generateVariableAssignment(VariableAssignmentNode* node);
    llvm::Value* generateExpression(ASTNode* node);
    void generatePrintStatement(PrintStatementNode* node);

public:
    LLVMCodeGen();
    void generateCode(std::unique_ptr<ProgramNode>& ast);
    void printLLVMIR();
};

#endif // LLVM_CODEGEN_HPP
