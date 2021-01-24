#include "pch.h"


#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../BazCryptCLI.h"
using namespace std;
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

TEST(BazCryptCli, goodWeather_message) {
    string path = "BazCryptCLI.exe";
    string msg = "SomeTextWhitoutWhiteSpaces";
    string key = "asimplepasswordtouse";
    int gen = 1500;
    int algorithm = 0;
    string fullcmd = path + " -m " + msg + " -p " + key + " -g " + to_string(gen) + " -a " + to_string(algorithm);
    int exitcode = system(fullcmd.c_str());
    EXPECT_EQ(exitcode, 0);
}
TEST(BazCryptCli, goodWeather_message2) {
    string path = "BazCryptCLI.exe";
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    int gen = 1500;
    int algorithm = 0;
    string fullcmd = path + " -m \"" + msg + "\" -p \"" + key + "\" -g " + to_string(gen) + " -a " + to_string(algorithm);
    int exitcode = system(fullcmd.c_str());
    EXPECT_EQ(exitcode, 0);
}

TEST(BazCryptCli, goodWeather_file) {
    string path = "BazCryptCLI.exe";
    string msgPath = "../../BazCryptLIBTest/small.txt";
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    int gen = 1500;
    int algorithm = 0;
    //string fullcmd = path + " -m \"" + msg + "\" -p \"" + key + "\" -g " + to_string(gen) + " -a " + to_string(algorithm);
    string fullcmd = path + " -f " + msgPath + " -p " + key + " -g " + to_string(gen) + " -a " + to_string(algorithm);
    // ENCR
    int exitcode = system(fullcmd.c_str());
    char* encoutput = new char[msg.size()];
    readFile(msgPath.c_str(), encoutput, msg.size());
    string encstr = string(encoutput, msg.size());
    EXPECT_NE(encstr, msg);
    // DECR
    int exitcode2 = system(fullcmd.c_str());
    char* output = new char[msg.size()];
    readFile(msgPath.c_str(), output, msg.size());
    string outputstr = string(output, msg.size());
    EXPECT_EQ(outputstr, msg);
    delete[] output;
    EXPECT_EQ(exitcode, 0);
    EXPECT_EQ(exitcode2, 0);
}