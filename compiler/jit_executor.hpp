#ifndef JIT_EXECUTOR_HPP
#define JIT_EXECUTOR_HPP

#include "llvm_codegen.hpp"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/Support/TargetSelect.h"
#include <memory>

class JITExecutor {
public:
    void execute(LLVMCodeGen& codegen);
};

#endif // JIT_EXECUTOR_HPP
