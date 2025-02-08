#include "jit_executor.hpp"
#include <iostream>

void JITExecutor::execute(LLVMCodeGen& codegen) {
    // Initialize LLVM JIT components
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // Create the JIT instance
    auto jit = llvm::orc::LLJITBuilder().create();
    if (!jit) {
        std::cerr << "Failed to create JIT!" << std::endl;
        return;
    }

    llvm::orc::LLJIT& lljit = **jit;  // ✅ Correct dereferencing

    // ✅ Fix: Move the module instead of cloning
    auto tsm = llvm::orc::ThreadSafeModule(
        codegen.releaseModule(),                    // ✅ No need to wrap again; already a unique_ptr
        std::make_unique<llvm::LLVMContext>()
    );



    // Add the module to the JIT
    if (auto err = lljit.addIRModule(std::move(tsm))) {
        std::cerr << "Error adding module to JIT!" << std::endl;
        return;
    }

    // Lookup the "main" function
    auto sym = lljit.lookup("main");
    if (!sym) {
        std::cerr << "Failed to find 'main' in module!" << std::endl;
        return;
    }

    // ✅ Fix: Use toPtr() directly instead of getAddress()
    auto mainFunc = sym->toPtr<int(*)()>();  // Cast to a function pointer
    int result = mainFunc();                 // Execute the function

    std::cout << "Program exited with code: " << result << std::endl;
}
