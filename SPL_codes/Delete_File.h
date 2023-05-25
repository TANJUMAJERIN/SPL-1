#include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
using namespace std;

void file_delete(const char* filePath) {
    //const char* filePath = "malware1.exe";

    if (std::remove(filePath) != 0) {
        std::perror("Failed to delete the file");
    } else {
        std::cout << "File deleted successfully." << std::endl;
    }

    //return 0;
}
//"C:/Users/Tanjuma Tabassum/OneDrive/Desktop/FINAL_SPL/malware1.exe";
