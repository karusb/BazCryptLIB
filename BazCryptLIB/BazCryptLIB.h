#pragma once
using namespace std;
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <string>


void evolve39318(bitset<20000> &s, int nbytes);
void evolve57630z(bitset<20000> &s, int nbytes);
void evolve57630b(bitset<20000> &s, int nbytes);
int* pokertest(bitset<8> &s);
string BazCrypt(string MESSAGE, string password, int generations, int algorithm = 0, bool verbose = false);