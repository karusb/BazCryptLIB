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
	int main()
	{
		return 0;
	}
	using namespace std;
	inline void evolve39318(bitset<8>* s, int nbytes);
	inline void evolve57630z(bitset<8>* s, int nbytes);
	inline void evolve57630b(bitset<8>* s, int nbytes);
	//inline int* pokertest(bitset<8>& s);
	int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm)
	{
		int gens = generations;
		int algo = algorithm;
		char* encMs = new char[messageLength];
		if (MESSAGE == nullptr || password == nullptr || output == nullptr) return  NULLPARAM;
		if (messageLength == 0 || passwordLength == 0 || generations == 0) return NULLSIZE;
		// Define Bitsets to hold message and CA world

		bitset<8>* bitM = new bitset<8>[messageLength];
		bitset<8>* bitKn = new bitset<8>[messageLength];
		bitKn->reset();
		bitset<8>* bitMs = new bitset<8>[messageLength];

		// Char to BITSET CONVERSIONS
		for (size_t i = 0; i < messageLength; ++i)
		{
			bitM[i] = bitset<8>(MESSAGE[i]);
		}

		if (passwordLength < messageLength)
		{
			for (size_t i = 0; i < messageLength; i++)
			{
				bitKn[i] = bitset<8>(password[i % passwordLength]);
			}
		}
		else
		{
			// This case is very unlikely considering a large message
			for (unsigned int i = 0; i < messageLength; ++i)
			{
				bitKn[i] = bitset<8>(password[i % passwordLength]);
			}
		}
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
			{
				bitMs[ic][i] = bitM[ic][i] ^ bitKn[ic][i]; // XOR KEY WITH THE MESSAGE
			}
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
	void evolve39318(bitset<8>* s, int nbytes)
	{
		// RULE 39318 4N
		std::bitset<8>* t = new std::bitset<8>[nbytes];

		t[0][0] = s[0][0] ^ s[0][1] ^ (s[nbytes - 1][8 - 2] | s[nbytes - 1][8 - 1]);
		t[0][1] = s[0][1] ^ s[0][2] ^ (s[nbytes - 1][8 - 1] | s[0][0]);
		t[nbytes - 1][8 - 1] = s[nbytes - 1][8 - 1] ^ s[0][0] ^ (s[nbytes - 1][8 - 3] | s[nbytes - 1][8 - 2]);

		for (int j = 0; j < nbytes; ++j)
		{
			if (j != 0)
			{
				t[j][0] = s[j][0] ^ s[j][1] ^ (s[j - 1][8 - 2] | s[j - 1][8 - 1]);
				t[j][1] = s[j][1] ^ s[j][2] ^ (s[j - 1][8 - 1] | s[j][0]);

			}
			for (int i = 2; i < 8 - 1; i++)
			{
				t[j][i] = s[j][i] ^ s[j][i + 1] ^ (s[j][i - 2] | s[j][i - 1]);
			}
			if (j != nbytes - 1)
			{
				t[j][8 - 1] = s[j + 1][8 - 1] ^ s[0][0] ^ (s[j + 1][8 - 3] | s[j + 1][8 - 2]);
			}
		}

		for (int i = 0; i < nbytes; i++)s[i] = t[i];
		delete[] t;
	}
	void evolve57630z(bitset<8>* s, int nbytes) //ZERO BOUNDARY EVOLUTION
	{
		std::bitset<8>* t = new std::bitset<8>[nbytes];

		// RULE 57630 4N
		t[0][0] = 0 ^ 0 ^ (s[0][0] | s[0][1]);
		t[0][1] = 0 ^ s[0][0] ^ (s[0][1] | s[0][2]);
		t[nbytes - 1][8 - 1] = s[nbytes - 1][8 - 3] ^ s[nbytes - 1][8 - 2] ^ (s[nbytes - 1][8 - 1] | 0);
		for (int j = 0; j < nbytes; ++j)
		{
			if (j != 0)
			{
				t[j][0] = s[j - 1][8 - 2] ^ s[j - 1][8 - 1] ^ (s[j][0] | s[j][1]);
				t[j][1] = s[j - 1][8 - 1] ^ s[j][0] ^ (s[j][1] | s[j][2]);
			}
			for (int i = 2; i < 8 - 1; i++)
			{
				t[j][i] = s[j][i - 2] ^ s[j][i - 1] ^ (s[j][i] | s[j][i + 1]);
			}
			if (j != nbytes - 1)
			{
				t[j][8 - 1] = s[j + 1][8 - 3] ^ s[j + 1][8 - 2] ^ (s[j + 1][8 - 1] | s[j][0]);
			}
		}

		for (int i = 0; i < nbytes; i++)s[i] = t[i];
		delete[] t;
	}
	void evolve57630b(bitset<8>* s, int nbytes) //CYCLIC BOUNDARY EVOLUTION
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
			{
				t[j][i] = s[j][i - 2] ^ s[j][i - 1] ^ (s[j][i] | s[j][i + 1]);
			}
			if (j != nbytes - 1)
			{
				t[j][8 - 1] = s[j + 1][8 - 3] ^ s[j + 1][8 - 2] ^ (s[j + 1][8 - 1] | s[j][0]);
			}
		}

		for (int i = 0; i < nbytes; i++)s[i] = t[i];
		delete[] t;
	}


	// Poker test functions takes bitsets of 8 which counts the occurences of the bit values given in array bitval
	//int* pokertest(bitset<8>& s)
	//{
	//	// Bit Values to search for poker test are defined here
	//	const bool bitval[16 * 4] = { 0,0,0,0,
	//		0,0,0,1,
	//		0,0,1,0,
	//		0,0,1,1,
	//		0,1,0,0,
	//		0,1,0,1,
	//		0,1,1,0,
	//		0,1,1,1,
	//		1,0,0,0,
	//		1,0,0,1,
	//		1,0,1,0,
	//		1,0,1,1,
	//		1,1,0,0,
	//		1,1,0,1,
	//		1,1,1,0,
	//		1,1,1,1
	//	};
	//	int statArr[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//	//
	//	for (int i = 0; i <= 5; i += 4) // iterates twice for 8 bits
	//	{
	//		for (int t = 0; t < 61; t += 4) //go through bitvals
	//		{
	//			if (s[i] == bitval[t] && s[i + 1] == bitval[t + 1] && s[i + 2] == bitval[t + 2] && s[i + 3] == bitval[t + 3]) // CHECK THE OCCURRENCES SPECIFIED IN BITVAL
	//			{
	//				if (t > 0)
	//				{
	//					statArr[t / 4] = statArr[t / 4] + 1;
	//				}
	//				else
	//				{
	//					statArr[t] = statArr[t] + 1;
	//				}
	//			}
	//		}
	//	}
	//	return statArr;
	//}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//const char* BazCrypt(const char* MESSAGE, const char* password, int generations, int algorithm, bool verbose)
	//{
	//
	//	int gens = generations;
	//	unsigned int ic;
	//	int algo = algorithm;
	//	string M = string(MESSAGE);   // Message
	//								  // Encrypted Message
	//	string encMs;
	//	string key = string(password); // Key
	//	string q; // quit parameter
	//
	//
	//	bool pass = true;
	//	bool readback = verbose;
	//
	//	int tick = 0;
	//	int gen = 0;
	//
	//	// Define Bitsets to hold message and CA world
	//
	//	bitset<8> *bitM = new bitset<8>[M.size()];;
	//	bitset<8> *bitK = new bitset<8>[M.size()];;
	//	bitset<8> *bitKn = new bitset<8>[M.size()];;
	//	bitset<20000> K;
	//	K.reset();
	//	bitset<20000> Kd;
	//	bitset<8> *bitMs = new bitset<8>[M.size()];;
	//
	//	int b = 0;
	//	int nbits = M.size() * 8; //bits in the string
	//	int by = 0;
	//
	//	// String to BITSET CONVERSIONS
	//	if (readback)cout << "Plain:";
	//	for (std::size_t i = 0; i < M.size(); ++i)
	//	{
	//		bitM[i] = bitset<8>(M[i]);
	//		if (readback)cout << char(bitM[i].to_ulong());
	//
	//	}
	//
	//	if (readback)cout << endl << endl << "IV:";
	//
	//	if (key.size() < M.size())
	//	{
	//		for (unsigned int i = 0; i<M.size(); i++)
	//		{
	//			int cur = (i%key.size());
	//
	//			bitKn[i] = bitset<8>(key[cur]);
	//			bitK[i] = bitset<8>(key[cur]);
	//
	//			if (readback)cout << char(bitKn[i].to_ulong());
	//		}
	//	}
	//	else
	//	{
	//		// This case is very unlikely considering a large message
	//		for (unsigned int i = 0; i<M.size(); ++i)
	//		{
	//			bitKn[i] = bitset<8>(key[i]);
	//			bitK[i] = bitset<8>(key[i]);
	//			if (readback)cout << char(bitKn[i].to_ulong());
	//		}
	//	}
	//
	//	//TRANSFER PASSWORD TO A BIGGER WORLD
	//	for (std::size_t i = 0; i < M.size() * 8; ++i)
	//	{
	//		K[i] = bitKn[b].test(i % 8); // check the values in bitKn
	//		if (i % 8 == 0)b += 1; // Increase b at every 8 iterations
	//	}
	//
	//
	//	do
	//	{
	//		by = 0;
	//		// EVOLUTION
	//		if (pass)
	//		{
	//			for (gen = 0; gen<gens; gen++)
	//			{
	//				switch (algo)
	//				{
	//				case 0:
	//					evolve57630b(K, M.size()); // This is done over the entire world doesnt need another loop
	//					break;
	//				case 1:
	//					evolve57630z(K, M.size());
	//
	//					break;
	//				case 2:
	//					evolve39318(K, M.size());
	//					break;
	//				default:
	//					evolve57630b(K, M.size());
	//					break;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			switch (algo)
	//			{
	//			case 0:
	//				evolve57630b(K, M.size());
	//				break;
	//			case 1:
	//				evolve57630z(K, M.size());
	//				break;
	//			case 2:
	//				evolve39318(K, M.size());
	//				break;
	//			default:
	//				evolve57630b(K, M.size());
	//				break;
	//			}
	//			gens = gens + 1;
	//		}
	//
	//
	//		// SPLIT THE WORLD IN SMALLER WORLDS
	//		for (int i = 0; i <= nbits - 1; i++)
	//		{
	//			bitKn[by].set(i % 8, K.test(i));
	//
	//			if (i % 8 == 0)by += 1;
	//		}
	//
	//		if (readback)cout << endl << "EVOLVED" << endl << endl;
	//		if (readback)cout << "Encrypted message:";
	//		//XOR OPERATION ENCRYPTION
	//		int oncount = 0;
	//
	//		encMs.clear();
	//		for (ic = 0; ic<M.size(); ic++)
	//		{
	//			for (int i = 0; i <= 7; i++)
	//				bitMs[ic][i] = bitM[ic][i] ^ bitKn[ic][i]; // XOR KEY WITH THE MESSAGE
	//														   // Bit count functions
	//			oncount += bitKn[ic].count();
	//			encMs.push_back(bitMs[ic].to_ulong());
	//
	//		}
	//
	//		double monoout = erfc(double(double(double(std::abs(double(oncount - ((M.size() * 8) - oncount)))) / double((sqrt(M.size() * 8)))) / sqrt(2))); // This is the monobit magic equation of NIST SP800
	//		if (monoout<0.01) // Needs to be >0.01
	//		{
	//			if (readback)cout << endl << "Failed to pass monobits test" << endl;
	//			if (readback)cout << endl << "Monobits2:" << ((oncount) * 100) / (8 * M.size()) << endl;
	//			pass = false;
	//		}
	//		else
	//		{
	//			pass = true;
	//			if (readback)cout << endl << "Pass..." << endl;
	//			if (readback)cout << endl << "Monobits2:" << ((oncount) * 100) / (8 * M.size()) << endl;
	//		}
	//
	//		//if (pass == false)system("CLS");
	//	} while (pass == false);
	//	
	//	////// STR TO CHAR CONV
	//	//char* retchar = new char[encMs.length()];
	//	size_t csize = strlen(encMs.c_str()) + sizeof(char);
	//	char* retptr = NULL;
	//	retptr = (char*)::CoTaskMemAlloc(csize);
	//	strcpy_s(retptr, csize, encMs.c_str());
	//
	//	delete[] bitM;
	//	delete[] bitK;
	//	delete[] bitKn;
	//	delete[] bitMs;
	//	return retptr;
	//
	//
	//
	//
	//
	//	//return encMs;
	//}
}