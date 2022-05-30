#include "export.h"

struct berResults
{
    double tot;
    double err;
    float ber;
    clock_t t1;
    clock_t t2;
};

uint8_t hammingDistance(uint8_t n1, uint8_t n2);
berResults calculateBer(std::string fpath1, std::string fpath2);
void createFile(const std::string name, const int count, const char value);
void createFileWithRandomValues(const std::string name, const int count, const char value);
char* getRandomBytes(const int count);
void printResult(berResults results);

int main(int argc, char* argv[])
{
    std::string arg1;
    std::string arg2;
    openLog("log.txt");
    if (argc == 3) {
        arg1 = argv[1];
        arg2 = argv[2];
        saveLog("Processing test files");
        berResults results = calculateBer(arg1, arg2);
        printResult(results);
    }
    else if (argc == 2 && argv[2] == "generate") {
        saveLog("Test files generation started");
        createFile("file1_test1.bin", 100, 0x55);
        saveLog("Created file: file1_test1.bin");
        createFile("file2_test1.bin", 100, 0x55);
        saveLog("Created file: file2_test1.bin"); 
        createFile("file1_test2.bin", 100, 0x55);
        saveLog("Created file: file1_test2.bin");
        createFileWithRandomValues("file2_test2.bin", 100, 0x55);
        saveLog("Created file: file2_test1.bin");
        createFile("file1_test3.bin", 400000000, 0x55);
        saveLog("Created file: file1_test3.bin");
        createFile("file2_test3.bin", 400000000, 0x50);
        saveLog("Created file: file2_test3.bin");
        saveLog("File generation completed");
        saveLog("Re-run program with proper arguments ie: ./HammingDistance.exe <test_file1> <test_file2>");
    }
    else {
        saveLog("Critical: Arguments not specified.");
        saveLog("Re-run program with proper arguments ie: ./HammingDistance.exe <test_file1> <test_file2>");
        return 1;
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

uint8_t hammingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}


berResults calculateBer(std::string fpath1, std::string fpath2)
{
    std::fstream firstFile, secondFile;
    berResults results;
    results.t1 = 0;
    results.t2 = 0;
    results.ber = 0;
    results.err = 0;
    results.tot = 0;

    saveLog("Calculating BER...");
    firstFile.open(fpath1.c_str(), std::ios::binary | std::ios::in);
    secondFile.open(fpath2.c_str(), std::ios::binary | std::ios::in);
    char a = 0x00;
    char b = 0x00;
    results.t1 = clock();

    while (!firstFile.eof())
    {
        firstFile >> a;
        secondFile >> b;
        if (!firstFile.eof())
        {
            results.err += hammingDistance(a, b);
            results.tot += 8;
        }
    }

    results.ber = (float)results.err / results.tot;
    results.t2 = clock();
    saveLog("BER calculations are done");
    return results;
}

void printResult(berResults results)
{
    std::stringstream message;
    message << "Results are: " << std::endl;
    message << "BER: " << results.ber << std::endl;
    message << "Tot: " << results.tot << std::endl;
    message << "Err: " << results.err << std::endl;
    message << "Calc time: " << ((float)results.t2 - results.t1) / CLOCKS_PER_SEC << " sec " << std::endl;
    saveLog(message.str());
}