#include<bits/stdc++.h>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <string.h>
#include <stdbool.h>
#include"Delete_File.h"
#include"SHA256.h"
#include"trie.h"
#include"PE_Header_parse.h"
#include"encode.h"
#include"decode.h"
typedef unsigned long DWORD;
using namespace std;
int check(string s){
    char keys[200][65];

    int track=0;
    int count = 0;
    struct TrieNode *root = getNode();
    int i;
    const char* fileName = s.c_str();
    std::ifstream file(s, std::ios::binary);

    if (file){

        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);


        std::string fileContent(fileSize, 0);
        file.read(&fileContent[0], fileSize);

        string hashvalue = SHA(fileContent);
        std::cout << "SHA-256 Hash: " << hashvalue << std::endl;
        const char *key=hashvalue.c_str();


//trie part


        FILE *fp = fopen("hashset.txt", "r");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return 1;
        }

        while (fscanf(fp, "%s", keys[count]) != EOF)
        {
            count++;
        }

        fclose(fp);


        struct TrieNode *root = getNode();


        int i;
        for (i = 0; i < count; i++)
            insert(root, keys[i]);


        if (search(root, key ))
            {cout << "This file is malware" << endl;
            track=-1;//}
            file.close();}

        //pe part check
        else
        {
            cout << "This file is not detect as malware by hash value matching , lets recheck by analysing pe header" << endl<<endl;


            unsigned short  majorImageVersion;
            unsigned long  checksum;
            unsigned short dllcharacteristics;
            unsigned long initializedData;
            //string s="malware2.exe";


            std::ifstream file(fileName, std::ios::binary);
            FILE *PpeFile;
            fopen_s(&PpeFile, fileName, "rb");

            if (PpeFile == NULL)
            {
                printf("Can't open file.\n");
                return 1;
            }

            unsigned long signature=ParseDOSHeader(fileName, PpeFile);
            if(signature==0x5A4D)
            {
                ParseNTHeaders(fileName, PpeFile,&initializedData,&checksum,&dllcharacteristics,&majorImageVersion);

                cout<<"Basic Info"<<endl;
                cout<<"--------------"<<endl;
                cout<<"Initialized data:   "<<initializedData<<endl;
                printf("hecksum:   0x%X\n", checksum);
                printf("DLL characteristics:   0x%X\n", dllcharacteristics);
                printf("major image version:   0x%X\n", majorImageVersion);
                int noOfSection=ParseSectionHeaders(fileName, file);
                //file.close();
                fclose(PpeFile);
                //cout<<"Number of Sections:  "<<noOfSection<<endl<<endl;

                char sections[noOfSection][8];
                for(int i=0; i<noOfSection; i++)
                    for(int j=0; j<8; j++)
                    {
                        sections[i][j]=SectionName[i][j];
                    }

                int i,j,k,l;

                int numNames = sizeof(sections) / sizeof(sections[0]);
                int numName = sizeof(known_section_names) / sizeof(known_section_names[0]);

                bool allPresent = true;

                for (int i = 0; i < numNames; ++i)
                {
                    bool found = false;
                    for (int j = 0; j < numName; ++j)
                    {
                        if (std::strcmp(sections[i], known_section_names[j]) == 0)
                        {
                            found = true;
                            //cout<<"found"<<found;
                            break;
                        }
                    }
                    if (!found)
                    {
                        allPresent = false;
                        //cout<<allPresent;
                        break;
                    }
                }

//int track=0;

                if(initializedData==0)
                {
                    cout<<"THIS FILE IS 'MALWARE'";
                    track=-1;

                }
                else if(!allPresent)
                {
                    cout<<"THIS FILE IS 'MALWARE'";
                    track=-1;

                }

                else if(dllcharacteristics==0&&majorImageVersion==0&&checksum==0)
                {
                    cout<<"THIS FILE IS 'MALWARE'";
                    track=-1;

                }

                else
                {
                    cout<<"THIS FILE IS 'NOT MALWARE'"<<endl;
                    track=0;

                }
            }

            else
            {
                cout<<endl<<"it is not PE file, so it is 'NOT MALWARE'"<<endl;

            }
            //cout<<"hey"<<endl;

            }


            if(track==-1)
            {

                cout<<"\nAs the file is malware, Do you want to Delete/Quarantine the file or want to do nothing with this file?"<<endl;
                cout<<"if so then select an option please-"<<endl;
                cout<<"1.Delete"<<endl;
                cout<<"2.Quarantine"<<endl;
                cout<<"3.Nothing"<<endl;
                int i;
                cin>>i;
                const char* filePath=fileName;
                if(i==1)
                {
                //const char* fileoo=s.c_str();
                file.close();
                //fclose(PpeFile);
                file_delete(filePath);
                /*if (std::remove(fileName) != 0) {
            std::perror("Failed to delete the file");
            std::cout << "Error code: " << errno << std::endl;
         } else {
        std::cout << "File deleted successfully." << std::endl;*/
    }


                else if(i==3)
                {
                    return 0;
                }
                else if(i==2)
                {
                    //encoding part
                    encodeFile(filePath);
                    int a;
                    cout<<"wanna have (decode) the file again?"<<endl<<"press 1 to decode the file, any number otherwise"<<endl;
                    cin>>a;
                    if(a==1)
                    {
                        decodeFile(filePath);
                    }
                    if(a!=1)
                    {
                        return 0;
                    }
                }

            }
        }














}
