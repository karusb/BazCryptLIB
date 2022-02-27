
#include <string>

#define GNULICENSE "    BazCrypt  Copyright (C) 2021  Baris Tanyeri \n  This program comes with ABSOLUTELY NO WARRANTY.\n This is free software, and you are welcome to redistribute it \n    under certain conditions; refer to GNU V3 Public License."

unsigned long getFileSize(const char* filepath);
bool readFile(const char* filepath, char* data, const unsigned long dataLength);
void DoWithOptions(char* encData, unsigned long long msgLen, bool fileInput, std::string infilename = "", std::string outfilename = "");
bool writeTxtFile(const char* filepath, char* data, const unsigned long dataLength);
bool writeBinFile(const char* filepath, char* data, const unsigned long dataLength);
void printHelp();