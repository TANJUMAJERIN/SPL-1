#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef unsigned long long int int64;
int64 Message[80];
const int64 Constants[80]
    = { 0x428a2f98d728ae22, 0x7137449123ef65cd,
        0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019,
        0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
        0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
        0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
        0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210,
        0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926,
        0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8,
        0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001,
        0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910,
        0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
        0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78a5636f43172f60,
        0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9,
        0xbef9a3f7b2c67915, 0xc67178f2e372532b,
        0xca273eceea26619c, 0xd186b8c721c0c207,
        0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
        0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493,
        0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
        0x5fcb6fab3ad6faec, 0x6c44198c4a475817
      };


string s1,Hex;
string decimal_to_binary(int decimal)
{
    string s1;
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
        s1.push_back(bin[i]);
    return s1;
}
string binary_to_hex(string s1)
{

    int len =s1.size();
    int i, j;
    char hex[8000];
    string Hex;
    j = 0;
    for (i = 0; i < len; i += 4)
    {
        int decimal = 0;
        int k;
        int pow=1;
        for (k = i+3; k >=i; k--)
        {
            decimal = decimal +(s1[k] -'0')*pow;
            pow=pow*2;
        }
        if (decimal < 10)
        {
            hex[j] = decimal + '0';
            Hex.push_back(hex[j]);
            j++;
        }
        else
        {
            hex[j] = decimal - 10 + 'A';
            Hex.push_back(hex[j]);
            j++;
        }
    }

    return Hex;
}

string SHA_512(string main_string)
{
    int64 A = 0x6a09e667f3bcc908;
    int64 B = 0xbb67ae8584caa73b;
    int64 C = 0x3c6ef372fe94f82b;
    int64 D = 0xa54ff53a5f1d36f1;
    int64 E = 0x510e527fade682d1;
    int64 F = 0x9b05688c2b3e6c1f;
    int64 G = 0x1f83d9abfb41bd6b;
    int64 H = 0x5be0cd19137e2179;

    int decimal[500];
    string binary_string;
    for(int i=0; i<main_string.size(); i++)
    {
        decimal[i]=int(main_string[i]);

        binary_string.append(decimal_to_binary(decimal[i]));
    }


    cout<<endl<<" binary string of main string\n"<<binary_string<<endl;
    string s1024;
    s1024=binary_string;
    int ori_length=binary_string.size();
    int  main_string_length=main_string.size()*8;

    string orilenbin;
    string orilen_binary=decimal_to_binary(main_string_length);
    for(int i=0; i<128-orilen_binary.size(); i++)
    {
        orilenbin.push_back('0');
    }
    orilenbin.append(orilen_binary);
    cout<<"\n\n128 bits representation of orilen\n"<<orilenbin<<endl;
    cout<<"size of 128 bits representation"<<orilenbin.size()<<endl<<endl;

    int tobeadded;
    int modded=ori_length%1024;
    if(1024-modded>=128)
        tobeadded=1024-modded;
    else if(1024-modded<128)
        tobeadded=2048-modded;
    s1024+='1';
    for (int y = 0; y < tobeadded - 129; y++)
    {
        s1024 += "0";
    }
    s1024.append(orilenbin);
    cout<<"updated string in binary after padding and adding 128 bits\n"<<s1024<<endl;
    cout<<"updated string er size n*1024 ache kina check  ->"<<s1024.size()<<endl;



    cout<<"\n now we convert the updated N*1024 string to hexadecimal string--->"<<endl;
    string hexadecimal_string=binary_to_hex(s1024);
    cout<<hexadecimal_string<<"\nfinal hexa string er size n*256 ache kina check "<<hexadecimal_string.size();

    int blocknumber=s1024.size()/1024;
    string Blocks[blocknumber];
    int chunknum=0;


    for (int i = 0; i < s1024.length();
            i += 1024, ++chunknum)
    {
        Blocks[chunknum] = s1024.substr(i, 1024);
    }


}



int main()
{
    string s;

    std::string file_name = "spl_file_demo.txt";
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
    std::cout << "String from the file is:\n " << main_string << std::endl;
    cout<<"size of the string: "<<main_string.size()<<endl;



    SHA_512(main_string);



}
