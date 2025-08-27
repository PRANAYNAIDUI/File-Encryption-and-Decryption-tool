#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

/**
 * Validates and converts a hexadecimal key string to binary data
 * @param keyHex The hexadecimal key string
 * @return The binary key data
 * @throws invalid_argument if key is invalid
 */
byteArray convertAndValidateKey(const string& keyHex) {
    // Check if key length is valid
    if (keyHex.length() < 8 || keyHex.length() > 32 || keyHex.length() % 2 != 0) {
        throw invalid_argument("Invalid key length. Must be between 8 and 32 characters.");
    }

    // Validate each character
    for (char c : keyHex) {
        if (!isxdigit(c)) {
            throw invalid_argument("Invalid character in key. Only hexadecimal characters allowed.");
        }
    }

    // Convert hex string to binary
    vector<unsigned char> keyBytes;
    for (size_t i = 0; i < keyHex.length(); ++i += 2) {
        string byteStr = keyHex.substr(i, 2);
        unsigned char byteValue = stoul(byteStr, nullptr, 16);
        keyBytes.push_back(byteValue);
    }

    return keyBytes;
}

// Example usage in main function
int main() {
    try {
        string userKey = "1a2b3c4d"; // Example hex key
        byteArray binaryKey = convertAndValidateKey(userKey);
        // Use binaryKey for encryption/decryption
    } catch (const invalid_argument& e) {
        cerr << "Key validation error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
