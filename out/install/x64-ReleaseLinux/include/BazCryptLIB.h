#pragma once
namespace BazCryptLIB
{
#define OK 0
#define NULLPARAM 1
#define NULLSIZE 2
#define UNKNERR 3
#pragma once
#ifdef __linux__ 
	extern "C" int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
#elif _WIN32
	extern "C" __declspec(dllexport) int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
#else

#endif
}