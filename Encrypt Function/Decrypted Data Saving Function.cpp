#include <fstream>
#include <string>
#include <stdexcept>

/**
 * Saves decrypted data to a new file.
 *
 * @param decryptedData Buffer containing the decrypted data
 * @param outputFilename Name of the output file
 * @param dataSize Size of the decrypted data
 * @return true if the operation was successful, false otherwise
 */
bool saveDecryptedData(const char* decryptedData, const std::string& outputFilename, size_t dataSize) {
    // Create a new file stream for writing
    std::ofstream outputFile(outputFilename, std::ios::out | std::ios::binary);
    
    // Check if the file was successfully opened
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open output file for writing.");
    }
    
    // Write the decrypted data to the file
    outputFile.write(decryptedData, dataSize);
    
    // Check if the write operation succeeded
    if (!outputFile.good()) {
        outputFile.close();
        throw std::runtime_error("Failed to write decrypted data to file.");
    }
    
    // Close the file stream
    outputFile.close();
    
    return true;
}
