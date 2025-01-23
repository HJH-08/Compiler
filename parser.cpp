#include <iostream>
#include <vector>
#include <cstdint>

// Define opcodes
enum OpCode {
    MOV = 0x01,
    ADD = 0x02,
    PRINT = 0x03,
    SUB = 0x04,
    JZ = 0x05,
    JMP = 0x06,
    HALT = 0xFF
};

// Virtual machine class
class VirtualMachine {
private:
    int32_t registers[8] = {0};  // 8 general-purpose registers
    std::vector<uint8_t> bytecode;
    size_t instructionPointer = 0;

public:
    void loadBytecode(const std::vector<uint8_t>& program) {
        bytecode = program;
        instructionPointer = 0;
    }

    void run() {
        while (instructionPointer < bytecode.size()) {
            uint8_t opcode = bytecode[instructionPointer++];
            switch (opcode) {
                case MOV: {
                    uint8_t reg = bytecode[instructionPointer++];
                    int8_t value = bytecode[instructionPointer++];
                    registers[reg] = value;
                    break;
                }
                case ADD: {
                    uint8_t dest = bytecode[instructionPointer++];
                    uint8_t src1 = bytecode[instructionPointer++];
                    uint8_t src2 = bytecode[instructionPointer++];
                    registers[dest] = registers[src1] + registers[src2];
                    break;
                }
                case SUB: {
                    uint8_t dest = bytecode[instructionPointer++];
                    uint8_t src1 = bytecode[instructionPointer++];
                    uint8_t src2 = bytecode[instructionPointer++];
                    registers[dest] = registers[src1] - registers[src2];
                    break;
                }
                case PRINT: {
                    uint8_t reg = bytecode[instructionPointer++];
                    std::cout << "Register R" << static_cast<int>(reg) << ": " << registers[reg] << std::endl;
                    break;
                }
                case HALT:
                    return;  // End program execution
                default:
                    std::cerr << "Unknown opcode: " << static_cast<int>(opcode) << std::endl;
                    return;
            }
        }
    }
};

int main() {
    // Example bytecode program
    std::vector<uint8_t> program = {
        0x01, 0x01, 0x0A,  // MOV R1, 10
        0x01, 0x02, 0x05,  // MOV R2, 5
        0x02, 0x03, 0x01, 0x02,  // ADD R3, R1, R2
        0x03, 0x03,        // PRINT R3
        0xFF               // HALT
    };

    // Run the virtual machine
    VirtualMachine vm;
    vm.loadBytecode(program);
    vm.run();

    return 0;
}
