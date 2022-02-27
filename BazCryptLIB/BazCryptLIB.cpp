/*
BazCrypt 4 Neighbourhood Cellular Automata XOR Encryption
Copyright (C) 2017  Baris Tanyeri

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/
// STD
#include <bitset>
#include <string.h>
// Header 
#include "BazCryptLIB.h"

namespace BazCryptLIB
{
	using namespace std;
	inline void evolve39318(bitset<8>* s, unsigned long nbytes);
	inline void evolve57630z(bitset<8>* s, unsigned long nbytes);
	inline void evolve57630b(bitset<8>* s, unsigned long nbytes);

	int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm)
	{
		int gens = generations;
		int algo = algorithm;
		char* encMs = new char[messageLength];
		if (MESSAGE == nullptr || password == nullptr || output == nullptr)
			return  NULLPARAM;
		if (messageLength == 0 || passwordLength == 0 || generations == 0)
			return NULLSIZE;

		// Define Bitsets to hold message and CA world
		bitset<8>* bitM = new bitset<8>[messageLength];
		bitset<8>* bitKn = new bitset<8>[messageLength];
		bitKn->reset();
		bitset<8>* bitMs = new bitset<8>[messageLength];

		// Char to BITSET CONVERSIONS
		for (size_t i = 0; i < messageLength; ++i)
			bitM[i] = bitset<8>(MESSAGE[i]);

		for (size_t i = 0; i < messageLength; ++i)
			bitKn[i] = bitset<8>(password[i % passwordLength]);

		// EVOLUTION
		for (size_t curgen = 0; curgen < generations; ++curgen)
		{
			switch (algo)
			{
			case 0:
				evolve57630b(bitKn, messageLength);
				break;
			case 1:
				evolve57630z(bitKn, messageLength);
				break;
			case 2:
				evolve39318(bitKn, messageLength);
				break;
			default:
				evolve57630b(bitKn, messageLength);
				break;
			}
		}
		//XOR OPERATION
		for (size_t ic = 0; ic < messageLength; ic++)
		{
			for (int i = 0; i < 8; i++)
				bitMs[ic][i] = bitM[ic][i] ^ bitKn[ic][i]; // XOR KEY WITH THE MESSAGE

			encMs[ic] = static_cast<char>(bitMs[ic].to_ulong());
		}
		size_t csize = messageLength * sizeof(char);
		memcpy(output, encMs, csize);

		delete[] bitM;
		delete[] bitKn;
		delete[] bitMs;
		delete[] encMs;

		return OK;
	}

	// EVOLVE FUNCTIONS
	void evolve39318(bitset<8>* s, unsigned long nbytes)
	{
		// RULE 39318 4N
		std::bitset<8>* t = new std::bitset<8>[nbytes];

		t[0][0] = s[0][0] ^ s[0][1] ^ (s[nbytes - 1][8 - 2] | s[nbytes - 1][8 - 1]);
		t[0][1] = s[0][1] ^ s[0][2] ^ (s[nbytes - 1][8 - 1] | s[0][0]);
		t[nbytes - 1][8 - 1] = s[nbytes - 1][8 - 1] ^ s[0][0] ^ (s[nbytes - 1][8 - 3] | s[nbytes - 1][8 - 2]);

		for (size_t j = 0; j < nbytes; ++j)
		{
			if (j != 0)
			{
				t[j][0] = s[j][0] ^ s[j][1] ^ (s[j - 1][8 - 2] | s[j - 1][8 - 1]);
				t[j][1] = s[j][1] ^ s[j][2] ^ (s[j - 1][8 - 1] | s[j][0]);
			}
			for (int i = 2; i < 8 - 1; i++)
				t[j][i] = s[j][i] ^ s[j][i + 1] ^ (s[j][i - 2] | s[j][i - 1]);

			if (j != nbytes - 1)
				t[j][8 - 1] = s[j + 1][8 - 1] ^ s[0][0] ^ (s[j + 1][8 - 3] | s[j + 1][8 - 2]);
		}

		for (size_t i = 0; i < nbytes; i++)
			s[i] = t[i];

		delete[] t;
	}

	void evolve57630z(bitset<8>* s, unsigned long nbytes) //ZERO BOUNDARY EVOLUTION
	{
		std::bitset<8>* t = new std::bitset<8>[nbytes];

		// RULE 57630 4N
		t[0][0] = 0 ^ 0 ^ (s[0][0] | s[0][1]);
		t[0][1] = 0 ^ s[0][0] ^ (s[0][1] | s[0][2]);
		t[nbytes - 1][8 - 1] = s[nbytes - 1][8 - 3] ^ s[nbytes - 1][8 - 2] ^ (s[nbytes - 1][8 - 1] | 0);
		for (size_t j = 0; j < nbytes; ++j)
		{
			if (j != 0)
			{
				t[j][0] = s[j - 1][8 - 2] ^ s[j - 1][8 - 1] ^ (s[j][0] | s[j][1]);
				t[j][1] = s[j - 1][8 - 1] ^ s[j][0] ^ (s[j][1] | s[j][2]);
			}
			for (int i = 2; i < 8 - 1; i++)
				t[j][i] = s[j][i - 2] ^ s[j][i - 1] ^ (s[j][i] | s[j][i + 1]);
			
			if (j != nbytes - 1)
				t[j][8 - 1] = s[j + 1][8 - 3] ^ s[j + 1][8 - 2] ^ (s[j + 1][8 - 1] | s[j][0]);
		}

		for (size_t i = 0; i < nbytes; i++)
			s[i] = t[i];

		delete[] t;
	}

	void evolve57630b(bitset<8>* s, unsigned long nbytes) //CYCLIC BOUNDARY EVOLUTION
	{
		std::bitset<8>* t = new std::bitset<8>[nbytes];

		// RULE 57630 4N
		t[0][0] = s[nbytes - 1][8 - 2] ^ s[nbytes - 1][8 - 1] ^ (s[0][0] | s[0][1]);
		t[0][1] = s[nbytes - 1][8 - 1] ^ s[0][0] ^ (s[0][1] | s[0][2]);
		t[nbytes - 1][8 - 1] = s[nbytes - 1][8 - 3] ^ s[nbytes - 1][8 - 2] ^ (s[nbytes - 1][8 - 1] | s[0][0]);
		for (int j = 0; j < nbytes; ++j)
		{
			if (j != 0)
			{
				t[j][0] = s[j - 1][8 - 2] ^ s[j - 1][8 - 1] ^ (s[j][0] | s[j][1]);
				t[j][1] = s[j - 1][8 - 1] ^ s[j][0] ^ (s[j][1] | s[j][2]);
			}

			for (int i = 2; i < 8 - 1; i++)
				t[j][i] = s[j][i - 2] ^ s[j][i - 1] ^ (s[j][i] | s[j][i + 1]);

			if (j != nbytes - 1)
				t[j][8 - 1] = s[j + 1][8 - 3] ^ s[j + 1][8 - 2] ^ (s[j + 1][8 - 1] | s[j][0]);
		}

		for (size_t i = 0; i < nbytes; i++)
			s[i] = t[i];

		delete[] t;
	}
}