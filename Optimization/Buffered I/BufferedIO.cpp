#include <iostream>
#include <fstream>
#include <cstring>

// Define buffer size for reading and writing
const size_t BUFFER_SIZE = 4096;

// Function to encrypt file using buffered I/O
bool encryptFile(const char* inputFileName, const char* outputFileName, const char* key) {
    // Open input and output files in binary mode
    FILE* inputFile = fopen(inputFileName, "rb");
    FILE* outputFile = fopen(outputFileName, "wb");
    
    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return false;
    }
    
    // Create a buffer to hold data chunks
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    // Read and process data in chunks
    while ((bytesRead = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, inputFile)) > 0) {
        // Encrypt the current chunk using XOR cipher
        for (size_t i = 0; i < bytesRead; i++) {
            buffer[i] ^= key[i % strlen(key)]; // XOR with key
        }
        
        // Write the encrypted chunk to output file
        if (fwrite(buffer, sizeof(unsigned char), bytesRead, outputFile) != bytesRead) {
            std::cerr << "Error writing to output file." << std::endl;
            fclose(inputFile);
            fclose(outputFile);
            return false;
        }
    }
    
    // Close files
    fclose(inputFile);
    fclose(outputFile);
    return true;
}

// Function to decrypt file using buffered I/O
bool decryptFile(const char* inputFileName, const char* outputFileName, const char* key) {
    // Open input and output files in binary mode
    FILE* inputFile = fopen(inputFileName, "rb");
    FILE* outputFile = fopen(outputFileName, "wb");
    
    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return false;
    }
    
    // Create a buffer to hold data chunks
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    // Read and process data in chunks
    while ((bytesRead = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, inputFile)) > 0) {
        // Decrypt the current chunk using XOR cipher (same as encryption)
        for (size_t i = 0; i < bytesRead; i++) {
            buffer[i] ^= key[i % strlen(key)]; // XOR with key again to decrypt
        }
        
        // Write the decrypted chunk to output file
        if (fwrite(buffer, sizeof(unsigned char), bytesRead, outputFile) != bytesRead) {
            std::cerr << "Error writing to output file." << std::endl;
            fclose(inputFile);
            fclose(outputFile);
            return false;
        }
    }
    
    // Close files
    fclose(inputFile);
    fclose(outputFile);
    return true;
}
