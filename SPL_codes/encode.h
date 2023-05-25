#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void encodeFile(const char* filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }


    std::vector<char> fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();


    for (char& byte : fileData) {
        byte = byte << 1;
    }

    std::ofstream outFile(filePath, std::ios::binary);


    outFile.write(fileData.data(), fileData.size());

    outFile.close();
    std::cout << "File encoding complete." << std::endl;
}




























/*#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void decodeFile(const char* filePath) {
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }

    char ch;
    while (file.read(&ch, sizeof(ch))) {
        ch = ch << 1; // Perform left shift by one bit

        // Move the file pointer back by one byte to overwrite the original byte
        file.seekp(-sizeof(ch), std::ios::cur);
        file.write(&ch, sizeof(ch));
        file.seekg(0, std::ios::cur); // Move the file pointer back to the next byte
    }

    file.close();
    std::cout << "file Decoding complete." << std::endl;
}*/

