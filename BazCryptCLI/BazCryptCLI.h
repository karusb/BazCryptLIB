
#include <string>

#define GNULICENSE "    BazCrypt  Copyright (C) 2021  Baris Tanyeri \n  This program comes with ABSOLUTELY NO WARRANTY.\n This is free software, and you are welcome to redistribute it \n    under certain conditions; refer to GNU V3 Public License."

unsigned long getFileSize(const char* filepath);
void readFile(const char* filepath, char* data, size_t dataLength);
void writeTxtFile(const char* filepath, char* data, size_t dataLength);
void writeBinFile(const char* filepath, char* data, size_t dataLength);
void encryptFile(const char* filePath, const char* password, const char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
void encryptText(const char* MESSAGE, const char* password, const char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);