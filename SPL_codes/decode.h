#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


void decodeFile(const char* filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }


    std::vector<char> fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();


    for (char& byte : fileData) {
        byte = byte >> 1;
    }

    std::ofstream outFile(filePath, std::ios::binary);


    outFile.write(fileData.data(), fileData.size());

    outFile.close();
    std::cout << "File decoding complete." << std::endl;
}




























