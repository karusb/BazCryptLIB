# BazCryptLIB
BazCrypt Encryption C++ Library

Allows you to perform BazCrypt Encryption with a simple function call.

BazCrypt is a symmetric XOR encryption algorithm that uses Cellular Automata to randomise the key that was initially provided as a password and provides extra security with generation number.


# Convention
```c++
void BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm, bool verbose);
```

 Message = char(8bit) array data that is to be encrypted/decrypted.
 
 password = char(8bit) array password that is to generate the IV for the encryption.
 
 output = pre allocated char(8bit) array which has the same size as the message 
 
 messageLength  = length of the Message array
 
 passwordLength = length of the password array
 
 generations = Non 0 integer number that determines the cycles of the algorithm. Also referred as PIN number.
 
 algorithm = Preferred algorithm of choice. Default is 0.
 - 0 = 57630b
 - 1 = 57630z
 - 2 = 39318
 
 verbose = Boolean value that determines whether there will be console output regarding the BazCrypt operations. Default is false.
# Dependencies
```c++
These will be automatically included in your program no need to redefine.
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
```
 # Example BazCrypt Call
 ```c++
 #include "BazCryptLIB.cpp"
int main()
{
	const char* mymessage = "This is a test plain text. This is also very important to hide!";
	const char* mykey = "asimplepasswordtouse";
	unsigned long keylen = 21;
	unsigned long msglen = 64;

	int mygeneration = 150;
	char* enc = new char[(int)msglen];
	// ENCRYPTION
	BazCrypt(mymessage, mykey,enc,msglen,keylen, mygeneration, 2, true);
	char* ret = new char[(int)msglen];
	// DECRYPTION
	BazCrypt(enc, mykey, ret, msglen, keylen, mygeneration, 2, true);

	cout << ret << endl;

	return 0;
}
```
![ProgramOutput](https://github.com/karusb/BazCryptLIB/raw/master/bazlib.jpg)
