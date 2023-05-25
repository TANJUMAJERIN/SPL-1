#include<bits/stdc++.h>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <string.h>
#include <stdbool.h>
#include <vector>
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
        //std::cout << "SHA-256 Hash: " << hashvalue << std::endl;
        const char *key=hashvalue.c_str();





        FILE *fp = fopen("hashset.txt", "r");
        if (fp == NULL)
        {
            printf("Error opening hashset file\n");
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
            {cout << "This file is Detected as Malware(hash)!" << endl<<endl;
            track=-1;//}
            file.close();}


        else
        {
            //cout << "This file is not detect as malware by hash value matching , lets recheck by analysing pe header" << endl<<endl;


            unsigned short  majorImageVersion;
            unsigned long  checksum;
            unsigned short dllcharacteristics;
            unsigned long initializedData;



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

                /*cout<<"Basic Info"<<endl;
                cout<<"--------------"<<endl;
                cout<<"Initialized data:   "<<initializedData<<endl;
                printf("hecksum:   0x%X\n", checksum);
                printf("DLL characteristics:   0x%X\n", dllcharacteristics);
                printf("major image version:   0x%X\n", majorImageVersion);*/
                int noOfSection=ParseSectionHeaders(fileName, file);

                fclose(PpeFile);


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

                            break;
                        }
                    }
                    if (!found)
                    {
                        allPresent = false;

                        break;
                    }
                }



                if(initializedData==0)
                {
                    cout<<"THIS FILE IS 'MALWARE'!!"<<endl<<endl;
                    track=-1;

                }
                else if(!allPresent)
                {
                    cout<<"THIS FILE IS 'MALWARE'"<<endl<<endl;
                    track=-1;

                }

                else if(dllcharacteristics==0&&majorImageVersion==0&&checksum==0)
                {
                    cout<<"THIS FILE IS 'MALWARE'"<<endl<<endl;
                    track=-1;

                }

                else
                {
                    cout<<"THIS FILE IS 'NOT MALWARE'"<<endl<<endl;
                    track=0;

                }
            }

            else
            {
                cout<<endl<<"it is not PE file"<<endl<<endl;
                return 0;

            }


            }

file.close();


            if(track==-1)
            {

                cout<<"\nDo you want to Delete/Quarantine the file or want to exit the program?"<<endl;
                cout<<"Select an option please-"<<endl;
                cout<<"  1.Delete"<<endl;
                cout<<"  2.Quarantine"<<endl;
                cout<<"  3.Exit"<<endl;
                int i;
                cin>>i;
                const char* filePath=fileName;
                if(i==1)
                {



                file_delete(filePath);

    }


                else if(i==3)
                {
                    return 0;
                }
                else if(i==2)
                {

                    encodeFile(filePath);
                    int a;
                    cout<<"wanna have (decode) the file again?"<<endl<<"press 1 to decode the file"<<endl;
                    cout<<"press 0 to exit"<<endl;
                    cin>>a;
                    if(a==1)
                    {
                        decodeFile(filePath);
                    }
                    if(a==0)
                    {
                        return 0;
                    }
                }

            }
        }


else
    cout<<" can't find the file "<<endl;











}
