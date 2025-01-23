#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <iostream>

// Virtual Machine Class
class VirtualMachine {
private:
    int32_t registers[8] = {0};  
    std::vector<uint8_t> bytecode;
    size_t instructionPointer = 0;

public:
    void loadBytecode(const std::vector<uint8_t>& program);
    void run();
};

#endif // INTERPRETER_HPP
