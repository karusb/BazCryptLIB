# BazCryptLIB
BazCrypt Encryption C++ Library

Allows you to perform BazCrypt Encryption/Decryption with a simple function call.

BazCrypt is a symmetric XOR encryption algorithm that uses Cellular Automata to randomise the key that was initially provided as a password and provides extra security with generation number.

## Use Cases
 - Text Encryption
 - Data Encryption
 - Communications Encryption (Only valid if password changes for each message)

## Pre-Compiled Binaries 
 - Download Linux
 - Download Windows

## Convention
```c++
int BazCrypt(const char* MESSAGE, const char* password, char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm);
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

 returns = Status after execution
 - 0 OK        = Finished succesfully.
 - 1 NULLPARAM = One or more input arrays are nullptrs.
 - 2 NULLSIZE  = One or more Length parameters are zero.

## Build
### Linux
  - Required build-essentials, cmake
  - Run these in terminal within the source directory:
   ```bash
   cmake .
   make install
   ```
  - Libraries are automatically installed i.e <BazCryptLIB.h>
### Windows 
  - Required Visual Studio
  - Run BazCryptLIB.sln and choose Release or DLL configuration, right click solution and click build.
  - Library will be located under x64/Release or x64/DLL depending on your preference


## Example BazCrypt Call
 ```c++
 #include "BazCryptLIB.h"
using namespace BazCryptLIB;
int main()
{
	const char* message = "This is a test plain text. This is also very important to hide!";
	const char* key = "asimplepasswordtouse";
	unsigned long keyLen = 21;
	unsigned long msgLen = 64;
	int generations = 1500;

	// ENCRYPTION
	char* encryptedMessage = new char[(int)msgLen];
	BazCrypt(message, key, encryptedMessage, msgLen, keyLen, generations, 2);

	// DECRYPTION
	char* decryptedMessage = new char[(int)msgLen];
	BazCrypt(encryptedMessage, key, decryptedMessage, msgLen, keyLen, generations, 2);

	return 0;
}
```
![ProgramOutput](https://github.com/karusb/BazCryptLIB/raw/master/bazlib.jpg)
