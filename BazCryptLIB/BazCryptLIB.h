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

inline void evolve39318(bitset<20000> &s, int nbytes);
inline void evolve57630z(bitset<20000> &s, int nbytes);
inline void evolve57630b(bitset<20000> &s, int nbytes);
inline int* pokertest(bitset<8> &s);
extern "C" __declspec(dllexport) char* BazCrypt(const char* MESSAGE, const char* password, int generations, int algorithm = 0, bool verbose = false);