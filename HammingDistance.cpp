#include "export.h"

struct berResults
{
    double tot;
    double err;
    float ber;
    clock_t t1;
    clock_t t2;
};

void createFile(const std::string name, const int count, const char value);
void createFileWithRandomValues(const std::string name, const int count, const char value);
char* getRandomBytes(const int count);
int main(int argc, char* argv[])
{
    std::string arg1;
    std::string arg2;
    openLog("log.txt");
    if (argc != 3) {
        saveLog("Critical: Arguments not specified.");
        saveLog("Re-run program with proper arguments ie: ./HammingDistance.exe <test_file1> <test_file2>");
        return 1;
    }
    else {
        arg1 = argv[1];
        arg2 = argv[2];
        std::string logMessage = "Provided arguments: arg1<" + arg1 + "> arg2<" + arg2 + ">";
        saveLog(logMessage);
    }
    return 0;
}

void createFile(const std::string name, const int count, const char value)
{
    std::fstream f;
    f.open(name.c_str(), std::ios::binary | std::ios::out);
    for (int i = 0; i < count; i++)
    {
        f.write((char*)&value, 1);
    }
    f.close();
}

void createFileWithRandomValues(const std::string name, const int count, const char value)
{
    std::fstream f;
    char* randomValue = new char[5];
    strcpy(randomValue, getRandomBytes(count));

    f.open(name.c_str(), std::ios::binary | std::ios::out);
    for (int i = 0; i < count; i++)
    {
        if (i % 10 == 0) {
            f.write((char*)&randomValue, 1);
        }
        else {

            f.write((char*)&value, 1);
        }
    }
    f.close();
}
char* getRandomBytes(const int count) {
    srand(time(NULL));
    int random = rand() % 5 + 2;
    std::string suffix = std::to_string((count / random) + random);
    std::string stringValue = "0x" + suffix;
    char* charValue = new char[5];
    strcpy(charValue, stringValue.c_str());
    return charValue;
}