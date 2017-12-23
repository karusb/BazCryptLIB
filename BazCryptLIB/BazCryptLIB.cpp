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


#include "BazCryptLIB.h"



///////////////////////// LIB TEST CODE 
//int main(int argc,char* argv[])
//{
//	string mymessage = "This is a test plain text. This is also very important to hide!";
//	string mykey = "asimplepasswordtouse";
//	string q;
//	bool ali = true;
//	int mygeneration = 150;
//	string myencryptmessage;
//	myencryptmessage = BazCrypt(mymessage, mykey, mygeneration,0,true);
//	cout << myencryptmessage << endl;
//	cin >> q;
//	myencryptmessage = BazCrypt(myencryptmessage, mykey, mygeneration);
//	cout << myencryptmessage  << endl;
//	cin >> q;
//	return 0;
//
//}
///////////////////////
char* BazCrypt(const char* MESSAGE, const char* password, int generations, int algorithm, bool verbose)
{

	int gens = generations;
	unsigned int ic;
	int algo = algorithm;
	string M = string(MESSAGE);   // Message
								  // Encrypted Message
	string encMs;
	string key = string(password); // Key
	string q; // quit parameter


	bool pass = true;
	bool readback = verbose;

	int tick = 0;
	int gen = 0;

	// Define Bitsets to hold message and CA world

	bitset<8> *bitM = new bitset<8>[M.size()];;
	bitset<8> *bitK = new bitset<8>[M.size()];;
	bitset<8> *bitKn = new bitset<8>[M.size()];;
	bitset<20000> K;
	K.reset();
	bitset<20000> Kd;
	bitset<8> *bitMs = new bitset<8>[M.size()];;

	int b = 0;
	int nbits = M.size() * 8; //bits in the string
	int by = 0;

	// String to BITSET CONVERSIONS
	if (readback)cout << "Plain:";
	for (std::size_t i = 0; i < M.size(); ++i)
	{
		bitM[i] = bitset<8>(M[i]);
		if (readback)cout << char(bitM[i].to_ulong());

	}

	if (readback)cout << endl << endl << "IV:";

	if (key.size() < M.size())
	{
		for (unsigned int i = 0; i<M.size(); i++)
		{
			int cur = (i%key.size());

			bitKn[i] = bitset<8>(key[cur]);
			bitK[i] = bitset<8>(key[cur]);

			if (readback)cout << char(bitKn[i].to_ulong());
		}
	}
	else
	{
		// This case is very unlikely considering a large message
		for (unsigned int i = 0; i<M.size(); ++i)
		{
			bitKn[i] = bitset<8>(key[i]);
			bitK[i] = bitset<8>(key[i]);
			if (readback)cout << char(bitKn[i].to_ulong());
		}
	}

	//TRANSFER PASSWORD TO A BIGGER WORLD
	for (std::size_t i = 0; i < M.size() * 8; ++i)
	{
		K[i] = bitKn[b].test(i % 8); // check the values in bitKn
		if (i % 8 == 0)b += 1; // Increase b at every 8 iterations
	}


	do
	{
		by = 0;
		// EVOLUTION
		if (pass)
		{
			for (gen = 0; gen<gens; gen++)
			{
				switch (algo)
				{
				case 0:
					evolve57630b(K, M.size()); // This is done over the entire world doesnt need another loop
					break;
				case 1:
					evolve57630z(K, M.size());

					break;
				case 2:
					evolve39318(K, M.size());
					break;
				default:
					evolve57630b(K, M.size());
					break;
				}
			}
		}
		else
		{
			switch (algo)
			{
			case 0:
				evolve57630b(K, M.size());
				break;
			case 1:
				evolve57630z(K, M.size());
				break;
			case 2:
				evolve39318(K, M.size());
				break;
			default:
				evolve57630b(K, M.size());
				break;
			}
			gens = gens + 1;
		}


		// SPLIT THE WORLD IN SMALLER WORLDS
		for (int i = 0; i <= nbits - 1; i++)
		{
			bitKn[by].set(i % 8, K.test(i));

			if (i % 8 == 0)by += 1;
		}

		if (readback)cout << endl << "EVOLVED" << endl << endl;
		if (readback)cout << "Encrypted message:";
		//XOR OPERATION ENCRYPTION
		int oncount = 0;

		encMs.clear();
		for (ic = 0; ic<M.size(); ic++)
		{
			for (int i = 0; i <= 7; i++)
				bitMs[ic][i] = bitM[ic][i] ^ bitKn[ic][i]; // XOR KEY WITH THE MESSAGE
														   // Bit count functions
			oncount += bitKn[ic].count();
			encMs.push_back(bitMs[ic].to_ulong());

		}

		double monoout = erfc(double(double(double(std::abs(double(oncount - ((M.size() * 8) - oncount)))) / double((sqrt(M.size() * 8)))) / sqrt(2))); // This is the monobit magic equation of NIST SP800
		if (monoout<0.01) // Needs to be >0.01
		{
			if (readback)cout << endl << "Failed to pass monobits test" << endl;
			if (readback)cout << endl << "Monobits2:" << ((oncount) * 100) / (8 * M.size()) << endl;
			pass = false;
		}
		else
		{
			pass = true;
			if (readback)cout << endl << "Pass..." << endl;
			if (readback)cout << endl << "Monobits2:" << ((oncount) * 100) / (8 * M.size()) << endl;
		}

		//if (pass == false)system("CLS");
	} while (pass == false);

	////// STR TO CHAR CONV
	//char* retchar = new char[encMs.length()];
	size_t csize = strlen(encMs.c_str()) + sizeof(char);
	char* retptr = NULL;
	retptr = (char*)::CoTaskMemAlloc(csize);
	strcpy_s(retptr, csize, encMs.c_str());

	return retptr;





	//return encMs;
}
// EVOLVE FUNCTIONS
// Inputs MUST be a bitset of 20000 bits
// Nbytes is the message size in bytes which determines the boundaries of evolution within the world
void evolve39318(bitset<20000> &s, int nbytes)
{

	// VERY REPETITIVE RESULTS?
	// RULE 39318 4N

	int i = 0, nbits = 0;
	nbits = nbytes * 8;

	std::bitset<20000> t;
	t[0] = s[0] ^ s[1] ^ (s[nbits - 2] | s[nbits - 1]);
	t[1] = s[1] ^ s[2] ^ (s[nbits - 1] | s[0]);
	t[nbits - 1] = s[nbits - 1] ^ s[0] ^ (s[nbits - 3] | s[nbits - 2]);
	for (i = 2; i < nbits - 1; i++)
	{
		t[i] = s[i] ^ s[i + 1] ^ (s[i - 2] | s[i - 1]);
	}

	for (i = 0; i <= nbits - 1; i++)s[i] = t[i];
}
void evolve57630z(bitset<20000> &s, int nbytes) //ZERO BOUNDARY EVOLUTION
{
	int i = 0, nbits = 0;
	nbits = nbytes * 8;

	std::bitset<20000> t;

	// RULE 57630 4N
	t[0] = 0 ^ 0 ^ (s[0] | s[1]);
	t[1] = 0 ^ s[0] ^ (s[1] | s[2]);
	t[nbits - 1] = s[nbits - 3] ^ s[nbits - 2] ^ (s[nbits - 1] | 0);
	for (i = 2; i < nbits - 1; i++)
	{
		t[i] = s[i - 2] ^ s[i - 1] ^ (s[i] | s[i + 1]);
	}

	for (i = 0; i <= nbits - 1; i++)s[i] = t[i];
}
void evolve57630b(bitset<20000> &s, int nbytes) //CYCLIC BOUNDARY EVOLUTION
{
	int i = 0, nbits = 0;
	nbits = nbytes * 8;

	std::bitset<20000> t;

	// RULE 57630 4N
	t[0] = s[nbits - 2] ^ s[nbits - 1] ^ (s[0] | s[1]);
	t[1] = s[nbits - 1] ^ s[0] ^ (s[1] | s[2]);
	t[nbits - 1] = s[nbits - 3] ^ s[nbits - 2] ^ (s[nbits - 1] | s[0]);
	for (i = 2; i < nbits - 1; i++)
	{
		t[i] = s[i - 2] ^ s[i - 1] ^ (s[i] | s[i + 1]);
	}

	for (i = 0; i <= nbits - 1; i++)s[i] = t[i];

}


// Poker test functions takes bitsets of 8 which counts the occurences of the bit values given in array bitval
int* pokertest(bitset<8> &s)
{
	// Bit Values to search for poker test are defined here
	const bool bitval[16 * 4] = { 0,0,0,0,
		0,0,0,1,
		0,0,1,0,
		0,0,1,1,
		0,1,0,0,
		0,1,0,1,
		0,1,1,0,
		0,1,1,1,
		1,0,0,0,
		1,0,0,1,
		1,0,1,0,
		1,0,1,1,
		1,1,0,0,
		1,1,0,1,
		1,1,1,0,
		1,1,1,1
	};
	int statArr[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//
	for (int i = 0; i <= 5; i += 4) // iterates twice for 8 bits
	{
		for (int t = 0; t<61; t += 4) //go through bitvals
		{
			if (s[i] == bitval[t] && s[i + 1] == bitval[t + 1] && s[i + 2] == bitval[t + 2] && s[i + 3] == bitval[t + 3]) // CHECK THE OCCURRENCES SPECIFIED IN BITVAL
			{
				if (t > 0)
				{
					statArr[t / 4] = statArr[t / 4] + 1;
				}
				else
				{
					statArr[t] = statArr[t] + 1;
				}
			}
		}
	}
	return statArr;
}