#include "assembler.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

// Function to trim leading and trailing spaces
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos) return ""; // If no valid characters, return empty string
    return str.substr(first, last - first + 1);
}

// Function to remove commas from a string
std::string removeCommas(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ',') {
            result += c;
        }
    }
    return result;
}

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

// Mapping instruction names to opcodes
std::unordered_map<std::string, uint8_t> instructionSet = {
    {"MOV", MOV}, {"ADD", ADD}, {"PRINT", PRINT},
    {"SUB", SUB}, {"JZ", JZ}, {"JMP", JMP}, {"HALT", HALT}
};

// Mapping register names to register numbers
std::unordered_map<std::string, uint8_t> registers = {
    {"R0", 0x00}, {"R1", 0x01}, {"R2", 0x02}, {"R3", 0x03},
    {"R4", 0x04}, {"R5", 0x05}, {"R6", 0x06}, {"R7", 0x07}
};

// Function to assemble human-readable assembly into bytecode
std::vector<uint8_t> assemble(const std::string& assemblyCode) {
    std::vector<uint8_t> bytecode;
    std::istringstream stream(assemblyCode);
    std::string line;

    while (std::getline(stream, line)) {
        line = trim(line);  // Trim whitespace
        if (line.empty()) continue;  // Skip empty lines

        std::istringstream lineStream(line);
        std::string opcode;
        lineStream >> opcode;

        if (instructionSet.find(opcode) == instructionSet.end()) {
            std::cerr << "Unknown instruction: " << opcode << std::endl;
            continue;
        }

        bytecode.push_back(instructionSet[opcode]); 

        if (opcode == "MOV") {
            std::string reg;
            int value;
            lineStream >> reg >> value;

            reg = removeCommas(trim(reg));

            if (registers.find(reg) == registers.end()) {
                std::cerr << "Unknown register: " << reg << std::endl;
                continue;
            }
            bytecode.push_back(registers[reg]);  
            bytecode.push_back(static_cast<uint8_t>(value));  
        } else if (opcode == "ADD" || opcode == "SUB") {
            std::string dest, src1, src2;
            lineStream >> dest >> src1 >> src2;

            dest = removeCommas(trim(dest));
            src1 = removeCommas(trim(src1));
            src2 = removeCommas(trim(src2));

            if (registers.find(dest) == registers.end() ||
                registers.find(src1) == registers.end() ||
                registers.find(src2) == registers.end()) {
                std::cerr << "Unknown register in ADD/SUB: " 
                          << dest << ", " << src1 << ", " << src2 << std::endl;
                continue;
            }

            bytecode.push_back(registers[dest]);  
            bytecode.push_back(registers[src1]);  
            bytecode.push_back(registers[src2]);  
        } else if (opcode == "PRINT") {
            std::string reg;
            lineStream >> reg;

            reg = removeCommas(trim(reg));

            if (registers.find(reg) == registers.end()) {
                std::cerr << "Unknown register: " << reg << std::endl;
                continue;
            }

            bytecode.push_back(registers[reg]);  
        }
    }
    return bytecode;
}
