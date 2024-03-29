#include <gtest/gtest.h>
#include "../BazCryptLIB/BazCryptLIB.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;
using namespace BazCryptLIB;

void readFileit(const char* filepath, char* data, unsigned long dataLength)
{
    std::ifstream input(filepath, std::ios::binary);

    std::vector<char> bytes(
        (std::istreambuf_iterator<char>(input)),
        (std::istreambuf_iterator<char>()));
    for (int i = 0; i < bytes.size() && i < dataLength; i++) {
        data[i] = bytes[i];
    }
    input.close();
}

void makeVector(const char* in, unsigned long inLen, std::vector<char>* out)
{
    out->reserve(inLen);
    for (unsigned long i = 0; i < inLen; ++i)
    {
        out->push_back(in[i]);
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
    else
    {
        cout << "Unable to open file";
        exit(1);
    }
}

void readFile(const char* filepath, char* data, const unsigned long dataLength)
{
    ifstream file(filepath, ios::in | ios::binary);
    if (file.is_open())
    {
        file.read(data, dataLength);
        file.seekg(0, ios::beg);
        file.close();
    }
    else      
    {
        cout << "Unable to open file";
        exit(1);
    }
}

TEST(BazCryptLibTest, goodWeather_algo1) {

    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 0;
    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);

    std::vector<char> msgv;
    makeVector(msg.c_str(), msglen, &msgv);
    std::vector<char> outv;
    makeVector(ret, msglen, &outv);
    std::vector<char> encv;
    makeVector(enc, msglen, &encv);
    EXPECT_NE(msgv, encv);
    EXPECT_EQ(msgv, outv);
}

TEST(BazCryptLibTest, goodWeather_0NilProof) {

    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = false;
    int gen = 1500;
    int algorithm = 0;
    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* encNil = new char[msglen];
    BazCrypt(msg.c_str(), "", encNil, msglen, 1, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);
    char* retNil = new char[msglen];
    BazCrypt(encNil, key.c_str(), retNil, msglen, keylen, gen, algorithm);


    std::vector<char> retv;
    makeVector(ret, msglen, &retv);
    std::vector<char> encNilv;
    makeVector(encNil, msglen, &encNilv);
    std::vector<char> retNilv;
    makeVector(retNil, msglen, &retNilv);
    std::vector<char> msgv;
    makeVector(msg.c_str(), msglen, &msgv);
    std::vector<char> outv;
    makeVector(ret, msglen, &outv);
    std::vector<char> encv;
    makeVector(enc, msglen, &encv);

    EXPECT_NE(encv, encNilv);
    EXPECT_NE(retv, retNilv);
    EXPECT_NE(msgv, encv);
    EXPECT_EQ(msgv, outv);
}

TEST(BazCryptLibTest, goodWeather_AlgoOutDiffer) {

    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = false;
    int gen = 1500;
    char* algo0 = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), algo0, msglen, keylen, gen, 0);
    char* algo1 = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), algo1, msglen, keylen, gen, 1);
    char* algo2 = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), algo2, msglen, keylen, gen, 2);


    std::vector<char> algo0v;
    makeVector(algo0, msglen, &algo0v);
    std::vector<char> algo1v;
    makeVector(algo1, msglen, &algo1v);
    std::vector<char> algo2v;
    makeVector(algo2, msglen, &algo2v);

    EXPECT_NE(algo0v, algo1v);
    EXPECT_NE(algo0v, algo2v);
    EXPECT_NE(algo1v, algo2v);
}

TEST(BazCryptLibTest, goodWeather_algo2) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 1;
    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);

    std::vector<char> msgv;
    makeVector(msg.c_str(), msglen, &msgv);
    std::vector<char> outv;
    makeVector(ret, msglen, &outv);
    std::vector<char> encv;
    makeVector(enc, msglen, &encv);
    EXPECT_NE(msgv, encv);
    EXPECT_EQ(msgv, outv);
}

TEST(BazCryptLibTest, goodWeather_algo3) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 2;
    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);

    std::vector<char> msgv;
    makeVector(msg.c_str(), msglen, &msgv);
    std::vector<char> outv;
    makeVector(ret, msglen, &outv);
    std::vector<char> encv;
    makeVector(enc, msglen, &encv);
    EXPECT_NE(msgv, encv);
    EXPECT_EQ(msgv, outv);

}

TEST(BazCryptLibTest, goodWeather_GenerationsAreDifferent_Algo0) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 0;

    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);
    gen = 1501;
    char* enc2 = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc2, msglen, keylen, gen, algorithm);
    char* ret2 = new char[msglen];
    BazCrypt(enc2, key.c_str(), ret2, msglen, keylen, gen, algorithm);

    std::vector<char> enc1v;
    makeVector(enc, msglen, &enc1v);
    std::vector<char> enc2v;
    makeVector(enc2, msglen, &enc2v);
    std::vector<char> ret1v;
    makeVector(ret, msglen, &ret1v);
    std::vector<char> ret2v;
    makeVector(ret2, msglen, &ret2v);
    EXPECT_NE(enc1v, enc2v);
    EXPECT_EQ(ret1v, ret2v);
    delete[] enc;
    delete[] enc2;
    delete[] ret;
    delete[] ret2;

}

TEST(BazCryptLibTest, goodWeather_GenerationsAreDifferent_Algo1) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 1;

    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);
    gen = 1501;
    char* enc2 = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc2, msglen, keylen, gen, algorithm);
    char* ret2 = new char[msglen];
    BazCrypt(enc2, key.c_str(), ret2, msglen, keylen, gen, algorithm);

    std::vector<char> enc1v;
    makeVector(enc, msglen, &enc1v);
    std::vector<char> enc2v;
    makeVector(enc2, msglen, &enc2v);
    std::vector<char> ret1v;
    makeVector(ret, msglen, &ret1v);
    std::vector<char> ret2v;
    makeVector(ret2, msglen, &ret2v);
    EXPECT_NE(enc1v, enc2v);
    EXPECT_EQ(ret1v, ret2v);
    delete[] enc;
    delete[] enc2;
    delete[] ret;
    delete[] ret2;
}

TEST(BazCryptLibTest, goodWeather_GenerationsAreDifferent_Algo2) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 2;

    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);
    gen = 1501;
    char* enc2 = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc2, msglen, keylen, gen, algorithm);
    char* ret2 = new char[msglen];
    BazCrypt(enc2, key.c_str(), ret2, msglen, keylen, gen, algorithm);

    std::vector<char> enc1v;
    makeVector(enc, msglen, &enc1v);
    std::vector<char> enc2v;
    makeVector(enc2, msglen, &enc2v);
    std::vector<char> ret1v;
    makeVector(ret, msglen, &ret1v);
    std::vector<char> ret2v;
    makeVector(ret2, msglen, &ret2v);
    EXPECT_NE(enc1v, enc2v);
    EXPECT_EQ(ret1v, ret2v);

    delete[] enc;
    delete[] enc2;
    delete[] ret;
    delete[] ret2;

}

TEST(BazCryptLibTest, badWeather_pinNil) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    int gen = 0;
    int algorithm = 2;

    char* enc = new char[msglen];
    auto r = BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    EXPECT_EQ(r, NULLSIZE);
}

TEST(BazCryptLibTest, badWeather_passNilSize) {
    string msg = "This is a test plain text. This is also very important to hide!";
    string key = "";
    unsigned long keylen = 0;
    unsigned long msglen = 64;
    int gen = 1000;
    int algorithm = 2;

    char* enc = new char[msglen];
    auto r = BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    EXPECT_EQ(r, NULLSIZE);
}

TEST(BazCryptLibTest, badWeather_passNil) {
    string msg = "This is a test plain text. This is also very important to hide!";
    const char* key = nullptr;
    unsigned long keylen = 21;
    unsigned long msglen = 64;
    int gen = 1000;
    int algorithm = 2;

    char* enc = new char[msglen];
    auto r = BazCrypt(msg.c_str(), key, enc, msglen, keylen, gen, algorithm);
    EXPECT_EQ(r, NULLPARAM);
}

TEST(BazCryptLibTest, badWeather_messageNilSize) {
    string msg = "";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 0;
    int gen = 1000;
    int algorithm = 2;

    char* enc = new char[msglen];
    auto r = BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    EXPECT_EQ(r, NULLSIZE);
}

TEST(BazCryptLibTest, badWeather_messageNil) {
    char* msg = nullptr;
    string key = "asimplepasswordtouse";
    unsigned long keylen = 21;
    unsigned long msglen = 0;
    int gen = 1000;
    int algorithm = 2;

    char* enc = new char[msglen];
    auto r = BazCrypt(msg, key.c_str(), enc, msglen, keylen, gen, algorithm);
    EXPECT_EQ(r, NULLPARAM);
}

TEST(BazCryptLibTest, badWeather_ShortMessage) {
    string msg = "This";
    string key = "asimplepasswordtouse";
    unsigned long keylen = 24;
    unsigned long msglen = 5;
    bool verbosity = true;
    int gen = 1500;
    int algorithm = 0;
    char* enc = new char[msglen];
    BazCrypt(msg.c_str(), key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);

    std::vector<char> msgv;
    makeVector(msg.c_str(), msglen, &msgv);
    std::vector<char> outv;
    makeVector(ret, msglen, &outv);
    std::vector<char> encv;
    makeVector(enc, msglen, &encv);
    EXPECT_NE(msgv, encv);
    EXPECT_EQ(msgv, outv);
}

TEST(BazCryptLibTest, goodWeather_DataFile) {

    string file = "bwbg.png";
    const unsigned long msglen = getFileSize(file.c_str());
    char* msg = new char[msglen];
    readFile(file.c_str(), msg, msglen);
    string key = "asimplepasswordtouse";
    unsigned long long keylen = 21;
    bool verbosity = false;
    int gen = 1500;
    int algorithm = 1;
    char* enc = new char[msglen];
    BazCrypt(msg, key.c_str(), enc, msglen, keylen, gen, algorithm);
    char* ret = new char[msglen];
    BazCrypt(enc, key.c_str(), ret, msglen, keylen, gen, algorithm);

    std::vector<char> msgv;
    makeVector(msg, msglen, &msgv);
    std::vector<char> outv;
    makeVector(ret, msglen, &outv);
    std::vector<char> encv;
    makeVector(enc, msglen, &encv);

    int totalunmatch = 0;
    for (unsigned long long i = 0; i < msglen; ++i)
    {
        if (msg[i] != ret[i])
        {
            std::cout << "[" << i << "] " << msgv[i] << " = " << outv[i] << std::endl;
            totalunmatch++;
        }
    }
    std::cout << "Total unmatch " << totalunmatch << "/" << msglen << std::endl;
    EXPECT_NE(msgv, encv);
    EXPECT_EQ(msgv, outv);
    EXPECT_EQ(totalunmatch, 0);
    delete[] enc;
    delete[] ret;
}
