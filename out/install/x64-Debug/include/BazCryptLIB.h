#pragma once
namespace BazCryptLIB
{
	using namespace std;
#define OK 0
#define NULLPARAM 1
#define NULLSIZE 2
#define UNKNERR 3

	extern "C" __declspec(dllexport) int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
}