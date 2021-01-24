# BazCryptLIB
[![Build Status](https://travis-ci.org/karusb/BazCryptLIB.svg?branch=master)](https://travis-ci.org/karusb/BazCryptLIB)
BazCrypt Encryption C++ Library

Allows you to perform BazCrypt Encryption/Decryption with a simple function call.

BazCrypt is a symmetric XOR encryption algorithm that uses Cellular Automata to randomise the key that was initially provided as a password and provides extra security with generation number.

## Use Cases
 - Text Encryption
 - Data Encryption
 - Communications Encryption (Only valid if password changes for each message)

## Pre-Compiled Binaries 
### Command Line Interface
 - [Download Linux](https://github.com/karusb/BazCryptLIB/releases/download/1.0.1/BazCryptCLI-v1.0-Linux64.zip)
 - [Download Windows](https://github.com/karusb/BazCryptLIB/releases/download/1.0.1/BazCryptCLI-v1.0-Windows64.zip)
#### Program Options
```
    -f  --file     Path to file to encrypt/decrypt
    -m  --message  Text data to encrypt
    -p  --pass     Password
    -g  --gen      Generation number, or known as pincode, use 4 digits atleast
    -o  --output   Path to output file, when specified input wont be overwritten
    -a  --algo     Optional algorithm selection, use 0 or 1 or 2, default is 0
    -L  --license  Prints software licence.
    -h  --help     Prints this text.

    File encryption/decryption example:
    bazcrypt -f \\path\\to\\file.txt -p strongpassword -g 1324

    Text encryption/decryption example:
    bazcrypt -m \"Plain Text\" -p strongpassword -g 1324 -o plain.txt
    bazcrypt -f plain.txt -p strongpassword -g 1324 -o plain.txt

```
### Library
 - [Download Linux](https://github.com/karusb/BazCryptLIB/releases/download/1.0.0/BazCrypt-v1.0-Linux64.zip)
 - [Download Windows](https://github.com/karusb/BazCryptLIB/releases/download/1.0.0/BazCrypt-v1.0-Windows64.zip)

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
  - CLI(CommandLineInterface) is automatically installed as "bazcrypt"
### Windows 
  - Required Visual Studio and CMake
  - Run BazCryptLIB.sln and choose Release or DLL configuration, right click solution and click build.
  - Library will be located under x64/Release or x64/DLL depending on your preference
  - CLI(CommandLineInterface) is automatically built as "bazcrypt.exe"


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
