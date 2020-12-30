#include <BazCryptLIB.h>
using namespace BazCryptLIB;
int main()
{
    char* msg = "This is a test plain text. This is also very important to hide!";
    const char* key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 0;
    char* enc = new char[msglen];
    return BazCrypt(msg, key, enc, msglen, keylen, gen, algorithm);
}