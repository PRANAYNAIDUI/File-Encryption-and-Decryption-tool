#include <fstream>
#include <iostream>

void xorFileEncryptDecrypt(const char *inputFile, const char *outputFile, unsigned char key) {
    std::ifstream inputStream(inputFile, std::ios::binary);
    std::ofstream outputStream(outputFile, std::ios::binary);

    if (!inputStream.is_open() || !outputStream.is_open()) {
        std::cerr << "Failed to open file";
        return;
    }

    char buffer[4096];
    while (inputStream.read(buffer, sizeof(buffer))) {
        for (size_t i = 0; i < inputStream.gcount(); ++i) {
            buffer[i] = buffer[i] ^ key;
        }
        outputStream.write(buffer, inputStream.gcount());
    }
    inputStream.close();
    outputStream.close();
}
