#include <iostream>
#include <string>
#include <stdexcept>

std::string getKeyFromUser() {
    std::string encryptionKey;
    bool validInput = false;

    do {
        // Prompt user for encryption key
        std::cout << "Please enter your encryption key: ";
        
        try {
            // Read input from user
            std::cin >> encryptionKey;
            
            // Basic validation: check if key is empty
            if (encryptionKey.empty()) {
                std::cerr << "Error: Encryption key cannot be empty." << std::endl;
                continue;
            }
            
            // Additional validation can be added here based on your requirements
            // For example: check length, allowed characters etc.
            
            validInput = true;
            
        } catch (const std::exception& e) {
            // Handle any input exceptions
            std::cerr << "Error: Invalid input. Please try again." << std::endl;
            std::cin.clear(); // Clear error flags
            std::cin.ignore(10000, '\n'); // Clear input buffer
        }
    } while (!validInput);

    return encryptionKey;
}

int main() {
    // Example usage:
    std::string key = getKeyFromUser();
    std::cout << "Encryption key: " << key << std::endl;
    return 0;
}
