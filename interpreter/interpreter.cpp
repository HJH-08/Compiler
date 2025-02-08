#include "interpreter.hpp"

// Load bytecode into the virtual machine
void VirtualMachine::loadBytecode(const std::vector<uint8_t>& program) {
    bytecode = program;
    instructionPointer = 0;
}

// Execute the bytecode instructions
void VirtualMachine::run() {
    while (instructionPointer < bytecode.size()) {
        uint8_t opcode = bytecode[instructionPointer++];
        switch (opcode) {
            case 0x01: {  // MOV
                uint8_t reg = bytecode[instructionPointer++];
                int8_t value = bytecode[instructionPointer++];
                registers[reg] = value;
                break;
            }
            case 0x02: {  // ADD
                uint8_t dest = bytecode[instructionPointer++];
                uint8_t src1 = bytecode[instructionPointer++];
                uint8_t src2 = bytecode[instructionPointer++];
                registers[dest] = registers[src1] + registers[src2];
                break;
            }
            case 0x03: {  // PRINT
                uint8_t reg = bytecode[instructionPointer++];
                std::cout << "Register R" << static_cast<int>(reg) << ": " << registers[reg] << std::endl;
                break;
            }
            case 0xFF:  // HALT
                return;
            default:
                std::cerr << "Unknown opcode: " << static_cast<int>(opcode) << std::endl;
                return;
        }
    }
}
