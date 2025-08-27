#include <iostream>
#include <fstream>
#include <string>
#include "encryption.h" // Include your encryption/decryption functions

using namespace std;

void displayMenu() {
    cout << "\n------------------------- File Encryption Tool -------------------------\n";
    cout << "1. Encrypt a file\n";
    cout << "2. Decrypt a file\n";
    cout << "3. Exit\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Enter your choice: ";
}

void handleUserInput() {
    int choice;
    string fileName, encryptedFileName, key;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore newline character after cin

        switch (choice) {
            case 1: {
                cout << "Enter the file name to encrypt: ";
                getline(cin, fileName);
                cout << "Enter the encrypted file name: ";
                getline(cin, encryptedFileName);
                cout << "Enter the encryption key: ";
                getline(cin, key);

                if (encryptFile(fileName, encryptedFileName, key)) {
                    cout << "File encrypted successfully!\n";
                } else {
                    cerr << "Failed to encrypt the file. Please check file paths and permissions.\n";
                }
                break;
            }
            case 2: {
                cout << "Enter the encrypted file name: ";
                getline(cin, fileName);
                cout << "Enter the decrypted file name: ";
                getline(cin, encryptedFileName);
                cout << "Enter the decryption key: ";
                getline(cin, key);

                if (decryptFile(fileName, encryptedFileName, key)) {
                    cout << "File decrypted successfully!\n";
                } else {
                    cerr << "Failed to decrypt the file. Please check file paths and permissions.\n";
                }
                break;
            }
            case 3:
                cout << "Exiting the program. Goodbye!\n";
                return;
            default:
                cerr << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    handleUserInput();
    return 0;
}
