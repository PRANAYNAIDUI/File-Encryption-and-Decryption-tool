#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

bool decryptFile(const string& encryptedFilename, const string& outputFilename, const string& key) {
    // Try to open the encrypted file for reading
    try {
        ifstream inputFile(encryptedFilename, ios::binary | ios::ate);
        if (!inputFile.is_open()) {
            throw invalid_argument("Failed to open input file for reading");
        }

        // Get file size
        size_t fileSize = inputFile.tellg();
        inputFile.seekg(0, ios::beg); // Reset position to beginning

        // Read file contents
        vector<char> buffer(fileSize);
        if (!inputFile.read(buffer.data(), fileSize)) {
            throw runtime_error("Failed to read from input file");
        }
        inputFile.close();

        // Try to open output file for writing
        try {
            ofstream outputFile(outputFilename, ios::binary);
            if (!outputFile.is_open()) {
                throw invalid_argument("Failed to open output file for writing");
            }

            // Perform decryption (XOR operation)
            for (char& c : buffer) {
                c ^= key[0]; // Simple XOR with single-byte key
            }

            // Write decrypted contents to output file
            if (!outputFile.write(buffer.data(), fileSize)) {
                throw runtime_error("Failed to write to output file");
            }
            outputFile.close();
            
            return true; // Success

        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            return false;
        } catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
            return false;
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
    
    return false; // If any other unexpected error occurs
}
