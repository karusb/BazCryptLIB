#pragma once
namespace BazCryptLIB
{
#define OK 0
#define NULLPARAM 1
#define NULLSIZE 2
#define UNKNERR 3
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif
#ifdef _WIN32
	EXTERNC __declspec(dllexport) int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
#else
	EXTERNC int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
#endif
}