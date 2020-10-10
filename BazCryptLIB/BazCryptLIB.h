#pragma once
using namespace std;
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <objbase.h>

#define OK 0
#define NULPARAM 1
#define NULLEN 2
#define UNKNERR 3

inline void evolve39318(bitset<8> *s, int nbytes);
inline void evolve57630z(bitset<8> *s, int nbytes);
inline void evolve57630b(bitset<8> *s, int nbytes);
inline int* pokertest(bitset<8> &s);
//extern "C" __declspec(dllexport) void BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
extern "C" __declspec(dllexport) int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
