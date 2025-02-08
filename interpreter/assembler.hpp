#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

// Function to remove leading/trailing spaces
std::string trim(const std::string& str);

// Function to remove commas from a string
std::string removeCommas(const std::string& str);

// Function to convert human-readable assembly to bytecode
std::vector<uint8_t> assemble(const std::string& assemblyCode);

#endif // ASSEMBLER_HPP
