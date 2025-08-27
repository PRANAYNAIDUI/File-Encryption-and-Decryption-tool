#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool decryptFile(const string& encryptedFilename, const string& outputFilename, const string& key) {
    // Open the encrypted file in binary read mode
    ifstream encryptedFile(encryptedFilename, ios::binary | ios::ate);
    if (!encryptedFile.is_open()) {
        cerr << "Error: Unable to open encrypted file for reading." << endl;
        return false;
    }

    // Get the size of the file
    size_t fileSize = encryptedFile.tellg();
    encryptedFile.seekg(0, ios::beg); // Reset the file pointer to beginning

    // Buffer to read data in chunks
    const size_t bufferSize = 4096;
    char* buffer = new char[bufferSize];
    size_t bytesRead;

    // Open the output file in binary write mode
    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file for writing." << endl;
        delete[] buffer;
        return false;
    }

    // Read and decrypt data in chunks
    while ((bytesRead = encryptedFile.read(buffer, bufferSize)) > 0) {
        // Apply XOR decryption with the key
        for (size_t i = 0; i < bytesRead; ++i) {
            buffer[i] = buffer[i] ^ key[i % key.length()];
        }
        // Write decrypted data to output file
        outputFile.write(buffer, bytesRead);
    }

    delete[] buffer;
    encryptedFile.close();
    outputFile.close();
    return true;
}
