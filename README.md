# BazCryptLIB
BazCrypt Encryption C++ Library

Allows you to perform BazCrypt Encryption with a simple function call.

BazCrypt is a symmetric encryption algorithm that uses Cellular Automata to randomise the key that was initially provided as a password.

Refer to the other repository for general purpose use : [https://github.com/karusb/1DCAEncryption](https://github.com/karusb/1DCAEncryption/releases)

# Convention
```c++
string BazCrypt(string MESSAGE, string password, int generations,int algorithm ,bool verbose)
```

 Message = String message that is to be encrypted/decrypted.
 
 password = String password that is to generate the IV for the encryption.
 
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
		string mymessage = "This is a test plain text. This is also very important to hide!";
		string mykey = "asimplepasswordtouse";
		string myencryptmessage,q;
		int mygeneration = 150;
    // ENCRYPTION
		myencryptmessage = BazCrypt(mymessage, mykey, mygeneration);
		cout << myencryptmessage << endl;
    // DECRYPTION
		myencryptmessage = BazCrypt(myencryptmessage, mykey, mygeneration);
		cout << myencryptmessage  << endl;
		cin >> q;
		return 0;
}
```
![ProgramOutput](https://github.com/karusb/BazCryptLIB/raw/master/bazlib.jpg)
