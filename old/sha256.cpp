#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
typedef unsigned long long int int64;
uint32_t Message[64];
const uint32_t Constants[]=
{
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2

};

string getHexFrom4bit(string bin)
{
    if (bin == "0000")
        return "0";
    if (bin == "0001")
        return "1";
    if (bin == "0010")
        return "2";
    if (bin == "0011")
        return "3";
    if (bin == "0100")
        return "4";
    if (bin == "0101")
        return "5";
    if (bin == "0110")
        return "6";
    if (bin == "0111")
        return "7";
    if (bin == "1000")
        return "8";
    if (bin == "1001")
        return "9";
    if (bin == "1010")
        return "a";
    if (bin == "1011")
        return "b";
    if (bin == "1100")
        return "c";
    if (bin == "1101")
        return "d";
    if (bin == "1110")
        return "e";
    if (bin == "1111")
        return "f";
    return NULL;
}


string getHexFromDecimal(uint32_t deci)
{
    string bin = bitset<32>(deci).to_string();

    string hex_str= "";
    string temp;

    for (unsigned int i = 0; i < bin.length(); i += 4)
    {
        temp = bin.substr(i, 4);
        hex_str += getHexFrom4bit(temp);
    }
    return hex_str;
}

uint32_t getDecFromBin(string bin)
{
    uint32_t value = bitset<32>(bin).to_ullong();
    return value;
}

uint32_t rotate_right(uint32_t x, int n)
{
    return (x >> n) | (x << (32 - n));
}

uint32_t shift_right(uint32_t x, int n)
{
    return (x >> n);
}

void message_schedeuler(string single_block)
{
    int nChunk = 0;

    for (int i = 0; i < (int)single_block.length(); i += 32, ++nChunk) Message[nChunk] = getDecFromBin(single_block.substr(i, 32));

    for (int g = 16; g < 64; ++g)
    {

        uint32_t WordA = rotate_right(Message[g - 2], 17) ^ rotate_right(Message[g - 2], 19) ^ shift_right(Message[g - 2], 10);//sigma 1
        uint32_t WordB = Message[g - 7];
        uint32_t WordC = rotate_right(Message[g - 15], 7) ^ rotate_right(Message[g - 15], 18) ^ shift_right(Message[g - 15], 3);//sigma0
        uint32_t WordD = Message[g - 16];

        uint32_t T = WordA + WordB + WordC + WordD;

        Message[g] = T;
    }
}

uint32_t maj(uint32_t a, uint32_t b, uint32_t c)
{
    return (a & b) ^ (b & c) ^ (c & a);
}

uint32_t Ch(uint32_t e, uint32_t f, uint32_t g)
{
    return (e & f) ^ (~e & g);
}

uint32_t sum_1(uint32_t e)
{
    return rotate_right(e, 6) ^ rotate_right(e, 11) ^ rotate_right(e, 25);
}

uint32_t sum_0(uint32_t a)
{
    return rotate_right(a, 2) ^ rotate_right(a, 13) ^ rotate_right(a, 22);
}

void round(uint32_t a, uint32_t b, uint32_t c,uint32_t d, uint32_t e, uint32_t f,uint32_t g, uint32_t h, int K)
{
    uint32_t T1 = h + Ch(e, f, g) + sum_1(e) + Message[K] + Constants[K];
    uint32_t T2 = sum_0(a) + maj(a, b, c);

    d = d + T1;
    h = T1 + T2;
}
string decimal_to_binary(uint32_t decimal)
{
    string str_binary;
    char bin[8];
    int i,j,s;
    for(i=7; i>=0; i--)
    {
        j=decimal % 2;
        if(j==0)
            bin[i]='0';


        else if(j==1)
            bin[i]='1';

        decimal = decimal / 2;

    }

    for(i=0; i<=7; i++)
        str_binary.push_back(bin[i]);
    return str_binary;
}
string SHA(string msg)
{

    uint32_t A = 0x6a09e667;
    uint32_t B = 0xbb67ae85;
    uint32_t C = 0x3c6ef372;
    uint32_t D = 0xa54ff53a;
    uint32_t E = 0x510e527f;
    uint32_t F = 0x9b05688c;
    uint32_t G = 0x1f83d9ab;
    uint32_t H = 0x5be0cd19;

    int n=msg.size();
    int decimal[n];


    string binary_str;
    for(int i=0; i<msg.size(); i++)
    {
        decimal[i]=int(msg[i]);

        binary_str.append(decimal_to_binary(decimal[i]));
    }

    cout<<"the binary string of main string"<<endl<<binary_str<<endl;

    int binary_msglen= binary_str.length();
    int pad_len;

    int last_block_len = binary_str.length() % 512;

    if (512 - last_block_len >= 64)
      pad_len = 512 - last_block_len;
    else
        pad_len = 1024 - last_block_len;

    binary_str += "1";
    for(int i = 0; i < pad_len - 65; i++)
        binary_str += "0";

    string lengthbits = std::bitset<64>(binary_msglen).to_string();


    binary_str += lengthbits;
    cout<<"the binary string after padding"<<endl<<binary_str<<endl<<"length of bin string after padd"<<binary_str.size()<<endl;
    int nBlock = binary_str.length() / 512;
    int iBlock = 0;

    string Blocks[nBlock];
    for (int i = 0; i < binary_str.length(); i += 512, ++iBlock) Blocks[iBlock] = binary_str.substr(i, 512);


    uint32_t previous_A, previous_B, previous_C, previous_D, previous_E, previous_F, previous_G, previous_H;
    for (int j = 0; j < nBlock; j++)
    {
        message_schedeuler(Blocks[j]);
        previous_A = A;
        previous_B = B;
        previous_C = C;
        previous_D = D;
        previous_E = E;
        previous_F = F;
        previous_G = G;
        previous_H = H;

        for (int i = 0; i < 64; i++)

        {
            uint32_t T1 = H + Ch(E, F, G) + sum_1(E) + Message[i] + Constants[i];
            uint32_t T2 = sum_0(A) + maj(A, B, C);

            H=G;
            G=F;
            F=E;
            E=D+T1;
            D=C;
            C=B;
            B=A;
            A=T1+T2;
        }

        A += previous_A;
        B += previous_B;
        C += previous_C;
        D += previous_D;
        E += previous_E;
        F += previous_F;
        G += previous_G;
        H += previous_H;
    }


    stringstream output;

    output << getHexFromDecimal(A);
    output << getHexFromDecimal(B);
    output << getHexFromDecimal(C);
    output << getHexFromDecimal(D);
    output << getHexFromDecimal(E);
    output << getHexFromDecimal(F);
    output << getHexFromDecimal(G);
    output << getHexFromDecimal(H);

    return output.str();
}

int main()
{

    string main_string;
    cout<<"enter the input string"<<endl;
    //cin>>main_string;
    std::getline(std::cin, main_string);

    /*std::string file_name = "spl_file_demo.txt";
    std::ifstream file(file_name);
    std::string main_string;
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            main_string+= line;
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    main_string.erase(std::remove(main_string.begin(), main_string.end(), ' '), main_string.end());
    std::cout << "\n\nString from the file is:\n" <<" "<< main_string <<endl<< std::endl;*/
    cout<<main_string.size()<<endl;
    string final_hashvalue=SHA(main_string);




    cout<<endl<<"the hash value is:"<<endl<<final_hashvalue<<endl;



}



