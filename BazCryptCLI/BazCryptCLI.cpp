#include "BazCryptCLI.h"
#include "BazCryptLIB.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "BazPO.hpp"

using namespace BazCryptLIB;
using namespace BazPO;
using namespace std;

int main(int argc, const char* argv[])
{
    Cli po(argc, argv, "Bazcrypt Command Line Interface");

    string defaultAlgorithm = "0";
    po.flag("-l", [&](const Option&) { cout << GNULICENSE << endl << endl << endl; }, "--license", "Prints software licence.").prioritize();

    auto& password = po.option("-p", "--password", "Password for the encryption/decryption").mandatory();
    auto& algorithm = po.option("-a", "--algorithm", "Optional algorithm selection, use 0 or 1 or 2, default is 0", defaultAlgorithm);
    StringConstraint algorithmConstraint(algorithm, { "0", "1", "2" });
    auto& generation = po.option("-g", "--generations", "Number of generations to run (sort of pin code), must be bigger than 1").mandatory();
    MinMaxConstraint<unsigned long> zeroLimit(generation, { 1, numeric_limits<unsigned long>::max() });

    auto& output = po.option("-o", "--output", "When defined, output is written to the specified file");

    FunctionMultiOption file(&po, "-f", [&](const Option& file) 
        {
            encryptFile(file.value(), password.value(), output.value(), getFileSize(file.value()), password.valueAs<std::string>().size(), generation.valueAs<int>(), algorithm.valueAs<int>());
        }, "--file", "File as chosen input to encrypt/decrypt");
    FunctionConstraint fileExists(file, [](const Option& file) { return ifstream(file.valueAs<std::string>(), ios::in).is_open(); }, "file doesn't exist");

    FunctionOption message(&po, "-m", [&](const Option& msg)
        {
            encryptText(msg.value(), password.value(), output.value(), msg.valueAs<std::string>().size(), password.valueAs<std::string>().size(), generation.valueAs<int>(), algorithm.valueAs<int>());
        }, "--message", "Text message to encrypt/decrypt");

    file.mandatory();
    message.mandatory();
    MutuallyExclusive userChoice(&po, file, message);

    po.userInputRequired();
    po.parse();

    return 0;
}

void encryptFile(const char* filePath, const char* password, const char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm)
{
    char* msgByte = new char[messageLength];
    char* enc = new char[messageLength];

    readFile(filePath, msgByte, messageLength);

    if (!BazCrypt(msgByte, password, enc, messageLength, passwordLength, generations, algorithm))
        if ("" != std::string(output))
            writeBinFile(output, enc, messageLength);
        else
            writeBinFile(filePath, enc, messageLength);
    delete[] msgByte;
    delete[] enc;
}

void encryptText(const char* MESSAGE, const char* password, const char* output, unsigned long messageLength, unsigned long passwordLength, int generations, int algorithm)
{
    char* enc = new char[messageLength];
    if (!BazCrypt(MESSAGE, password, enc, messageLength, passwordLength, generations, algorithm))
    {
        string outStr(enc, messageLength);
        cout << "------------------------ OUTPUT ------------------------" << endl;
        cout << outStr << endl;
        cout << "------------------------- END --------------------------" << endl;
        if ("" != std::string(output))
            writeTxtFile(output, enc, messageLength);
    }
    delete[] enc;
}

unsigned long getFileSize(const char* filepath)
{
    ifstream file(filepath, ios::in | ios::binary | ios::ate);
    auto size = file.tellg();
    file.seekg(0, ios::beg);
    file.close();
    return size;
}

void readFile(const char* filepath, char* data, size_t dataLength)
{
    ifstream file(filepath, ios::in | ios::binary);
    file.read(data, dataLength);
    file.seekg(0, ios::beg);
    file.close();
}

void writeBinFile(const char* filepath, char* data, size_t dataLength)
{
    ofstream file(filepath, ios::out | ios::binary);
    file.clear();
    file.write(data, dataLength);
    file.close();
}

void writeTxtFile(const char* filepath, char* data, size_t dataLength)
{
    ofstream file(filepath);
    file.clear();
    file.write(data, dataLength);
    file.close();
}
