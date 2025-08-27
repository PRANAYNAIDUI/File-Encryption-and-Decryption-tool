#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

// Function to calculate CRC32 checksum
uint32_t calculateCRC32(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for checksum calculation.");
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    uint32_t crc32 = 0xFFFFFFFF;
    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = file.readsome(buffer, sizeof(buffer))) > 0) {
        for (size_t i = 0; i < bytesRead; ++i) {
            crc32 = (crc32 >> 8) ^ table[(crc32 & 0xFF) ^ buffer[i]];
        }
    }

    return crc32 ^ 0xFFFFFFFF;
}

// Function to verify checksum
bool verifyChecksum(const std::string& originalFile, const std::string& decryptedFile) {
    uint32_t originalChecksum = calculateCRC32(originalFile);
    uint32_t decryptedChecksum = calculateCRC32(decryptedFile);

    return originalChecksum == decryptedChecksum;
}

// Example usage
int main() {
    try {
        // Encrypt and decrypt file as before...
        // After decryption:
        bool isValid = verifyChecksum("original_file.txt", "decrypted_file.txt");
        if (isValid) {
            std::cout << "Checksum verification successful. Data is intact." << std::endl;
        } else {
            std::cerr << "Checksum verification failed. Data may be corrupted." << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
