#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../BazCryptCLI/BazCryptCLI.h"
using namespace std;

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
/* UNIX-style OS. ------------------------------------------- */
static string path = "bazcrypt";
#else
static string path = "bazcrypt.exe";
#endif

void fileRead(const char* filepath, char* data, unsigned long dataLength)
{
    ifstream file(filepath, ios::in | ios::binary);
    file.read(data, dataLength);
    file.seekg(0, ios::beg);
    file.close();
}

TEST(BazCryptCliTest, goodWeather_message) {
    string msg = "SomeTextWhitoutWhiteSpaces";
    string key = "asimplepasswordtouse";
    int gen = 1500;
    int algorithm = 0;
    string fullcmd = path + " -m " + msg + " -p " + key + " -g " + to_string(gen) + " -a " + to_string(algorithm);
    int exitcode = system(fullcmd.c_str());
    EXPECT_EQ(exitcode, 0);
}
TEST(BazCryptCliTest, goodWeather_message2) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    int gen = 1500;
    int algorithm = 0;
    string fullcmd = path + " -m \"" + msg + "\" -p \"" + key + "\" -g " + to_string(gen) + " -a " + to_string(algorithm);
    int exitcode = system(fullcmd.c_str());
    EXPECT_EQ(exitcode, 0);
}

TEST(BazCryptCliTest, goodWeather_file) {
    string msgPath = "small.txt";
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    int gen = 1500;
    int algorithm = 0;
    string fullcmd = path + " -f " + msgPath + " -p " + key + " -g " + to_string(gen) + " -a " + to_string(algorithm);
    // ENCR
    int exitcode = system(fullcmd.c_str());
    char* encoutput = new char[msg.size()];
    fileRead(msgPath.c_str(), encoutput, msg.size());
    string encstr = string(encoutput, msg.size());
    EXPECT_NE(encstr, msg);
    // DECR
    int exitcode2 = system(fullcmd.c_str());
    char* output = new char[msg.size()];
    fileRead(msgPath.c_str(), output, msg.size());
    string outputstr = string(output, msg.size());
    EXPECT_EQ(outputstr, msg);
    delete[] output;
    EXPECT_EQ(exitcode, 0);
    EXPECT_EQ(exitcode2, 0);
}
