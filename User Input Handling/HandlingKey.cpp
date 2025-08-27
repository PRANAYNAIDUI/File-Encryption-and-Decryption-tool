#include <iostream>
#include <string>
#include <stdexcept>

// Function to get and validate the encryption key from user input
std::string getKeyFromUser() {
    const int MIN_KEY_LENGTH = 8;
    const int MAX_KEY_LENGTH = 32;
    
    std::string key;
    bool isValid = false;
    
    do {
        // Clear any previous error flags
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        
        std::cout << "Enter your encryption key (8-32 hexadecimal characters): ";
        std::cin >> key;
        
        try {
            if (key.length() < MIN_KEY_LENGTH || key.length() > MAX_KEY_LENGTH) {
                std::cerr << "Error: Key length must be between " << MIN_KEY_LENGTH << " and " << MAX_KEY_LENGTH << " characters." << std::endl;
                continue;
            }
            
            // Check if all characters are hexadecimal
            for (char c : key) {
                if (!isxdigit(c)) {
                    throw std::invalid_argument("Non-hex character found");
                }
            }
            
            // If we reach here, the key is valid
            isValid = true;
            
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Error: Key contains invalid characters. Only hexadecimal characters (0-9, a-f, A-F) are allowed." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << std::endl;
        }
        
    } while (!isValid);
    
    return key;
}
