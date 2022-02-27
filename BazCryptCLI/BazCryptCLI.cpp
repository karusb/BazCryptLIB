#include "BazCryptCLI.h"
#include "BazCryptLIB.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace BazCryptLIB;
using namespace std;

int main(int argc, char* argv[])
{
    int gens;
    int algo = 0;
    string msg;   // Message
    char* msgByte;
    unsigned long msgLen = 0;
    unsigned long keyLen = 0;
    char* enc = nullptr; // Encrypted Message
    string key; // Key
    string fname; //filename parameter
    string newfname; // output filename

    bool pass = true;
    bool filechoice = false;
    bool interactive = false;
    bool statM = false;
    bool newout = false;
    int tick = 0;
    int argno = 1;

    if (argc < 2)
    {
        cout << "No or few input arguments, interactive mode starting..." << endl;
        interactive = true;
    }
    else
    {
        bool waitingOptionInput = false;
        while (argv[argno] != NULL)
        {
            if (argv[argno] == string("-h") || argv[argno] == string("-help") || argv[argno] == string("--help"))
            {
                printHelp();
                return 0;
            }
            if (argv[argno] == string("-f") || argv[argno] == string("--file"))
            {
                filechoice = true;
                fname = argv[argno + 1];
                tick += 1;
                waitingOptionInput = true;
            }
            if (argv[argno] == string("-o") || argv[argno] == string("--output"))
            {
                newout = true;
                newfname = argv[argno + 1];
                tick += 1;
                waitingOptionInput = true;
            }
            if (argv[argno] == string("-g") || argv[argno] == string("--gen"))
            {
                gens = atoi(argv[argno + 1]);
                if (gens > 0)tick += 1;
                waitingOptionInput = true;
            }
            if (argv[argno] == string("-m") || argv[argno] == string("--message"))
            {
                statM = true;
                msg = argv[argno + 1];
                tick += 1;
                waitingOptionInput = true;
            }
            if (argv[argno] == string("-p") || argv[argno] == string("--pass"))
            {
                key = argv[argno + 1];
                tick += 1;
                waitingOptionInput = true;
            }
            if ((argv[argno] == string("-a") || argv[argno] == string("--algo")))
            {
                algo = atoi(argv[argno + 1]);
                waitingOptionInput = true;
            }
            if (argv[argno] == string("-L") || argv[argno] == string("--license"))
            {
                // GNU License Output //
                cout << GNULICENSE << endl << endl << endl;
            }
            argno += 1;
        }
        if (tick < 3)
        {
            cout << "Not enough combination of inputs, starting in interactive mode with defaults..." << endl;
            interactive = true;
        }
    }
    if (interactive)
    {
        // GNU License Output //
        cout << GNULICENSE << endl << endl << endl;

        cout << "Input generation number: ";
        cin >> gens;
        cout << "Input pass phrase: ";
        cin >> key;
        cout << "Choose : File (1) , Plain Text (0): ";
        cin >> filechoice;
    }
    int exitCode = -1;
    if (filechoice)
    {
        filechoiceloc:
        if (interactive)
            cout << "Please enter the filename path" << endl;
        if (interactive)
            cin >> fname;
        msgLen  = getFileSize(fname.c_str());
        msgByte = new char[msgLen];
        enc = new char[msgLen];
        bool fileOk = readFile(fname.c_str(), msgByte, msgLen);
        if (!fileOk)
        {
            interactive = true;
            goto filechoiceloc;
        }
        exitCode = BazCrypt(msgByte, key.c_str(), enc, msgLen, key.size(), gens, algo);
        delete[] msgByte;
    }
    else
    {

        if (!statM)
        {
            cout << "Input message: ";
            cin.ignore();
            std::getline(std::cin, msg, '\n');
        }
        msgLen = msg.size();
        enc = new char[msgLen];
        exitCode = BazCrypt(msg.c_str(), key.c_str(), enc, msgLen, key.size(), gens, algo);
    }
    if(exitCode == 0)
        DoWithOptions(enc, msgLen, filechoice, fname, newfname);
    delete[] enc;

    return exitCode;
}

void DoWithOptions(char* encData, unsigned long long msgLen, bool fileInput, string infilename, string outfilename )
{
    if (fileInput)
    {
        if (outfilename != "")
            writeBinFile(outfilename.c_str(), encData, msgLen);
        else
            writeBinFile(infilename.c_str(), encData, msgLen);
    }
    else
    {
        string outStr = string(encData, msgLen);
        cout << "------------------------ OUTPUT ------------------------" << endl;
        cout << outStr << endl;
        cout << "------------------------- END --------------------------" << endl;
        if (outfilename != "")
            writeTxtFile(outfilename.c_str(), encData, msgLen);
    }
}

unsigned long getFileSize(const char* filepath)
{
    ifstream file(filepath, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
        unsigned long size;
        size = file.tellg();
        file.seekg(0, ios::beg);
        file.close();
        return size;
    }
    else cout << "Unable to open file";
    return 0;
}

bool readFile(const char* filepath, char* data, const unsigned long dataLength)
{
    ifstream file(filepath, ios::in | ios::binary);
    if (file.is_open())
    {
        file.read(data, dataLength);
        file.seekg(0, ios::beg);
        file.close();
        return true;
    }
    else
    {
        cout << "Unable to open file";
        return false;
    }
}

bool writeBinFile(const char* filepath, char* data, const unsigned long dataLength)
{
    ofstream file(filepath, ios::out | ios::binary);
    if (file.is_open())
    {
        file.clear();
        file.write(data, dataLength);
        file.close();
        return true;
    }
    else
    {
        cout << "Unable to open file";
        return false;
    }
}

bool writeTxtFile(const char* filepath, char* data, const unsigned long dataLength)
{
    ofstream file(filepath);
    if (file.is_open())
    {
        file.clear();
        file.write(data, dataLength);
        file.close();
        return true;
    }
    else
    {
        cout << "Unable to open file";
        return false;
    }
}

void printHelp()
{
    cout << "Bazcrypt Command Line Interface Program Options :" << endl;
    cout << "-f  --file     Path to file to encrypt/decrypt" << endl;
    cout << "-m  --message  Text data to encrypt" << endl;
    cout << "-p  --pass     Password" << endl;
    cout << "-g  --gen      Generation number, or known as pincode, use 4 digits atleast" << endl;
    cout << "-o  --output   Path to output file, when specified input wont be overwritten" << endl;
    cout << "-a  --algo     Optional algorithm selection, use 0 or 1 or 2, default is 0" << endl;
    cout << "-L  --license  Prints software licence. " << endl;
    cout << "-h  --help     Prints this text. " << endl << endl;
    cout << "Text encryption example: " << endl;
    cout << "bazcrypt -m \"Plain Text\" -p strongpassword -g 1324" << endl;
    cout << "File encryption example: " << endl;
    cout << "bazcrypt -f \\path\\to\\file.txt -p strongpassword -g 1324" << endl;
}
