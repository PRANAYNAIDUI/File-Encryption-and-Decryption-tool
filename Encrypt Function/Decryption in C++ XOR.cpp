#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<char> readEncryptedFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Get the size of the file
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the entire file into a vector
    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    if (!file) {
        throw std::runtime_error("Failed to read file: " + filename);
    }

    return buffer;
}
