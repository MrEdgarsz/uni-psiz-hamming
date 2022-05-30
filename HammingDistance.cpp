#include "export.h"

struct berResults
{
    double tot;
    double err;
    float ber;
    clock_t t1;
    clock_t t2;
};

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
