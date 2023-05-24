#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long QWORD;
typedef unsigned long LONG;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;

#define ___IMAGE_NT_OPTIONAL_HDR32_MAGIC       0x10b
#define ___IMAGE_NT_OPTIONAL_HDR64_MAGIC       0x20b
#define ___IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
#define ___IMAGE_DOS_SIGNATURE                 0x5A4D

#define ___IMAGE_SIZEOF_SHORT_NAME              8
#define ___IMAGE_SIZEOF_SECTION_HEADER          40
//image dos header
typedef struct __IMAGE_DOS_HEADER {
    WORD   e_magic;
    WORD   e_cblp;
    WORD   e_cp;
    WORD   e_crlc;
    WORD   e_cparhdr;
    WORD   e_minalloc;
    WORD   e_maxalloc;
    WORD   e_ss;
    WORD   e_sp;
    WORD   e_csum;
    WORD   e_ip;
    WORD   e_cs;
    WORD   e_lfarlc;
    WORD   e_ovno;
    WORD   e_res[4];
    WORD   e_oemid;
    WORD   e_oeminfo;
    WORD   e_res2[10];
    LONG   e_lfanew;
} ___IMAGE_DOS_HEADER, * ___PIMAGE_DOS_HEADER;

//image optional header

typedef struct __IMAGE_OPTIONAL_HEADER {
    WORD    Magic;
    BYTE    MajorLinkerVersion;
    BYTE    MinorLinkerVersion;
    DWORD   SizeOfCode;
    DWORD   SizeOfInitializedData;
    DWORD   SizeOfUninitializedData;
    DWORD   AddressOfEntryPoint;
    DWORD   BaseOfCode;
    DWORD   BaseOfData;
    DWORD   ImageBase;
    DWORD   SectionAlignment;
    DWORD   FileAlignment;
    WORD    MajorOperatingSystemVersion;
    WORD    MinorOperatingSystemVersion;
    WORD    MajorImageVersion;
    WORD    MinorImageVersion;
    WORD    MajorSubsystemVersion;
    WORD    MinorSubsystemVersion;
    DWORD   Win32VersionValue;
    DWORD   SizeOfImage;
    DWORD   SizeOfHeaders;
    DWORD   CheckSum;
    WORD    Subsystem;
    WORD    DllCharacteristics;
    DWORD   SizeOfStackReserve;
    DWORD   SizeOfStackCommit;
    DWORD   SizeOfHeapReserve;
    DWORD   SizeOfHeapCommit;
    DWORD   LoaderFlags;
    DWORD   NumberOfRvaAndSizes;

} ___IMAGE_OPTIONAL_HEADER32, * ___PIMAGE_OPTIONAL_HEADER32;

//image file header
typedef struct __IMAGE_FILE_HEADER {
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
} ___IMAGE_FILE_HEADER, * ___PIMAGE_FILE_HEADER;

//image nt header
//image nt header er moddhe thake file header ar optional header

typedef struct __IMAGE_NT_HEADERS {
    DWORD Signature;
    ___IMAGE_FILE_HEADER FileHeader;
    ___IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} ___IMAGE_NT_HEADERS32, * ___PIMAGE_NT_HEADERS32;

//section header
typedef struct __IMAGE_SECTION_HEADER {
    unsigned char  Name[___IMAGE_SIZEOF_SHORT_NAME];
    union {
        DWORD   PhysicalAddress;
        DWORD   VirtualSize;
    } Misc;
    DWORD   VirtualAddress;
    DWORD   SizeOfRawData;
    DWORD   PointerToRawData;
    DWORD   PointerToRelocations;
    DWORD   PointerToLinenumbers;
    WORD    NumberOfRelocations;
    WORD    NumberOfLinenumbers;
    DWORD   Characteristics;
} ___IMAGE_SECTION_HEADER, * ___PIMAGE_SECTION_HEADER;

    ___IMAGE_DOS_HEADER     PEFILE_DOS_HEADER;
    ___IMAGE_NT_HEADERS32   PEFILE_NT_HEADERS;

    // DOS HEADER
    DWORD PEFILE_DOS_HEADER_EMAGIC;
    LONG  PEFILE_DOS_HEADER_LFANEW;
   DWORD PEFILE_NT_HEADERS_SIGNATURE;

    // NT_HEADERS.FileHeader
    WORD PEFILE_NT_HEADERS_FILE_HEADER_MACHINE;
    WORD PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS;
    WORD PEFILE_NT_HEADERS_FILE_HEADER_SIZEOF_OPTIONAL_HEADER;

    // NT_HEADERS.OptionalHeader
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_MAGIC;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_CODE;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_INITIALIZED_DATA;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_UNINITIALIZED_DATA;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_ADDRESSOF_ENTRYPOINT;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_BASEOF_CODE;
    ULONGLONG PEFILE_NT_HEADERS_OPTIONAL_HEADER_IMAGEBASE;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_SECTION_ALIGNMENT;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_FILE_ALIGNMENT;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_IMAGE;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_HEADERS;
    DWORD PEFILE_NT_HEADERS_OPTIONAL_HEADER_CHECKSUM;
    WORD  PEFILE_NT_HEADERS_OPTIONAL_HEADER_DLLCHARACTERISTICS;

    // SECTION HEADERS
    ___PIMAGE_SECTION_HEADER PEFILE_SECTION_HEADERS;



//parser

//DOS header parse
void ParseDOSHeader(char* _NAME, FILE* _Ppefile) {
    char* NAME;
    FILE* Ppefile;
    NAME = _NAME;
	Ppefile = _Ppefile;
	fseek(Ppefile, 0, SEEK_SET);
	fread(&PEFILE_DOS_HEADER, sizeof(___IMAGE_DOS_HEADER), 1, Ppefile);

	PEFILE_DOS_HEADER_EMAGIC = PEFILE_DOS_HEADER.e_magic;
	PEFILE_DOS_HEADER_LFANEW = PEFILE_DOS_HEADER.e_lfanew;

	//print
	printf(" DOS HEADER:\n");
	printf(" -----------\n\n");

	printf(" Magic: 0x%X\n", PEFILE_DOS_HEADER_EMAGIC);
	printf(" File address of new exe header: 0x%X\n", PEFILE_DOS_HEADER_LFANEW);


}
//NT header parse
void ParseNTHeaders(char* _NAME, FILE* _Ppefile) {
    char* NAME;
    FILE* Ppefile;
    NAME = _NAME;
	Ppefile = _Ppefile;
	fseek(Ppefile, PEFILE_DOS_HEADER.e_lfanew, SEEK_SET);
	fread(&PEFILE_NT_HEADERS, sizeof(PEFILE_NT_HEADERS), 1, Ppefile);

	PEFILE_NT_HEADERS_SIGNATURE = PEFILE_NT_HEADERS.Signature;

	PEFILE_NT_HEADERS_FILE_HEADER_MACHINE = PEFILE_NT_HEADERS.FileHeader.Machine;
	PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS = PEFILE_NT_HEADERS.FileHeader.NumberOfSections;
	PEFILE_NT_HEADERS_FILE_HEADER_SIZEOF_OPTIONAL_HEADER = PEFILE_NT_HEADERS.FileHeader.SizeOfOptionalHeader;

	PEFILE_NT_HEADERS_OPTIONAL_HEADER_MAGIC = PEFILE_NT_HEADERS.OptionalHeader.Magic;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_CODE = PEFILE_NT_HEADERS.OptionalHeader.SizeOfCode;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_INITIALIZED_DATA = PEFILE_NT_HEADERS.OptionalHeader.SizeOfInitializedData;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_UNINITIALIZED_DATA = PEFILE_NT_HEADERS.OptionalHeader.SizeOfUninitializedData;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_ADDRESSOF_ENTRYPOINT = PEFILE_NT_HEADERS.OptionalHeader.AddressOfEntryPoint;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_BASEOF_CODE = PEFILE_NT_HEADERS.OptionalHeader.BaseOfCode;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_IMAGEBASE = PEFILE_NT_HEADERS.OptionalHeader.ImageBase;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_SECTION_ALIGNMENT = PEFILE_NT_HEADERS.OptionalHeader.SectionAlignment;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_FILE_ALIGNMENT = PEFILE_NT_HEADERS.OptionalHeader.FileAlignment;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_IMAGE = PEFILE_NT_HEADERS.OptionalHeader.SizeOfImage;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_HEADERS = PEFILE_NT_HEADERS.OptionalHeader.SizeOfHeaders;
	PEFILE_NT_HEADERS_OPTIONAL_HEADER_CHECKSUM = PEFILE_NT_HEADERS.OptionalHeader.CheckSum;
    PEFILE_NT_HEADERS_OPTIONAL_HEADER_DLLCHARACTERISTICS = PEFILE_NT_HEADERS.OptionalHeader.DllCharacteristics;
    //print info
    printf(" NT HEADERS:\n");
	printf(" -----------\n\n");

	printf(" PE Signature: 0x%X\n", PEFILE_NT_HEADERS_SIGNATURE);

	printf("\n File Header:\n\n");
	printf("   Machine: 0x%X\n", PEFILE_NT_HEADERS_FILE_HEADER_MACHINE);
	printf("   Number of sections: 0x%X\n", PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS);
	printf("   Size of optional header: 0x%X\n", PEFILE_NT_HEADERS_FILE_HEADER_SIZEOF_OPTIONAL_HEADER);

	printf("\n Optional Header:\n\n");
	printf("   Magic: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_MAGIC);
	printf("   Size of code section: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_CODE);
	printf("   Size of initialized data: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_INITIALIZED_DATA);
	printf("   Size of uninitialized data: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_UNINITIALIZED_DATA);
	printf("   Address of entry point: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_ADDRESSOF_ENTRYPOINT);
	printf("   RVA of start of code section: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_BASEOF_CODE);
	printf("   Desired image base: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_IMAGEBASE);
	printf("   Section alignment: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_SECTION_ALIGNMENT);
	printf("   File alignment: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_FILE_ALIGNMENT);
	printf("   Size of image: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_IMAGE);
	printf("   Size of headers: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_SIZEOF_HEADERS);
	printf("   CHECKSUM: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_CHECKSUM);
    printf("   DLLCHARACTERISTICS: 0x%X\n", PEFILE_NT_HEADERS_OPTIONAL_HEADER_DLLCHARACTERISTICS);



}

    //section header parse



void ParseSectionHeaders(char* _NAME, FILE* _Ppefile) {
    char* NAME;
    FILE* Ppefile;
    NAME = _NAME;
	Ppefile = _Ppefile;

	PEFILE_SECTION_HEADERS = new ___IMAGE_SECTION_HEADER[PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS];
	for (int i = 0; i < PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS; i++) {
		int offset = (PEFILE_DOS_HEADER.e_lfanew + sizeof(PEFILE_NT_HEADERS)) + (i * ___IMAGE_SIZEOF_SECTION_HEADER);
		fseek(Ppefile, offset, SEEK_SET);
		fread(&PEFILE_SECTION_HEADERS[i], ___IMAGE_SIZEOF_SECTION_HEADER, 1, Ppefile);
	}
	//print section header info
	printf(" SECTION HEADERS:\n");
	printf(" ----------------\n\n");

	for (int i = 0; i < PEFILE_NT_HEADERS_FILE_HEADER_NUMBER0F_SECTIONS; i++) {
		printf("   * %.8s:\n", PEFILE_SECTION_HEADERS[i].Name);
		printf("        VirtualAddress: 0x%X\n", PEFILE_SECTION_HEADERS[i].VirtualAddress);
		printf("        VirtualSize: 0x%X\n", PEFILE_SECTION_HEADERS[i].Misc.VirtualSize);
		printf("        PointerToRawData: 0x%X\n", PEFILE_SECTION_HEADERS[i].PointerToRawData);
		printf("        SizeOfRawData: 0x%X\n", PEFILE_SECTION_HEADERS[i].SizeOfRawData);
		printf("        Characteristics: 0x%X\n\n", PEFILE_SECTION_HEADERS[i].Characteristics);
	}

}

//main function


int main() {
    char* filename = "demo_exe_file.exe";

    FILE *PpeFile;
    fopen_s(&PpeFile, filename, "rb");

    if (PpeFile == NULL) {
        printf("Can't open file.\n");
        return 1;
    }

    ParseDOSHeader(filename, PpeFile);
    ParseNTHeaders(filename, PpeFile);
	ParseSectionHeaders(filename, PpeFile);

    return 0;
}















