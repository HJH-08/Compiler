#include "llvm_codegen.hpp"
#include "jit_executor.hpp"
#include "parser.hpp"
#include "lexer.hpp"

int main() {
    std::string code = R"(
        let x = 10;
        let y = 5;
        let sum = x + y;
        print(sum);
    )";

    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    std::unique_ptr<ProgramNode> ast = parser.parse();

    LLVMCodeGen llvmGen;
    llvmGen.generateCode(ast);

    // Print the LLVM IR (for debugging purposes)
    llvmGen.printLLVMIR();

    // Execute the generated code using JIT
    JITExecutor jitExecutor;
    jitExecutor.execute(llvmGen);

    return 0;
}
