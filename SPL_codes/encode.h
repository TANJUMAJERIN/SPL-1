#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
void encodeFile(const char* filePath) {
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Failed to open file!" << std::endl;
        return;
    }

    char ch;
    while (file.read(&ch, sizeof(ch))) {
        ch = ch >> 1; // Perform right shift by one bit

        // Move the file pointer back by one byte to overwrite the original byte
        file.seekp(-sizeof(ch), std::ios::cur);
        file.write(&ch, sizeof(ch));
        file.seekg(0, std::ios::cur); // Move the file pointer back to the next byte
    }

    file.close();
    cout<<"file quarentien complete"<<endl;
}



