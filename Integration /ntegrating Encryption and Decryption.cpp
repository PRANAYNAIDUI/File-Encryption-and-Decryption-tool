// file_encryptor.h
#ifndef FILE_ENCRYPTOR_H
#define FILE_ENCRYPTOR_H

#include <fstream>
#include <string>
#include <cstdint>

class FileEncryptor {
public:
    FileEncryptor(const std::string& key) : key_(key) {}
    
    bool encryptFile(const std::string& inputPath, const std::string& outputPath);
    bool decryptFile(const std::string& inputPath, const std::string& outputPath);
    
    uint32_t calculateChecksum(const std::string& filePath);
    
protected:
    std::string key_;
    
    // Helper function to read file contents
    std::string readFileContents(const std::string& filePath);
    
    // Helper function to write file contents
    bool writeFileContents(const std::string& filePath, const std::string& data);
    
    // Helper function to perform XOR operation
    std::string applyXOR(const std::string& data, const std::string& key);
    
    // Helper function to display progress
    void showProgress(uint64_t bytesRead, uint64_t totalBytes);
};

#endif // FILE_ENCRYPTOR_H
