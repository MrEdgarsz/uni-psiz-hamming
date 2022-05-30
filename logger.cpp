#define _CRT_SECURE_NO_WARNINGS
#include "export.h"

std::fstream logFile;

void openLog(std::string fileName)
{
    logFile.open(fileName.c_str(), std::ios_base::app);
    if (!logFile.good() == true)
    {
        std::cout << "Cannot open log file " << "log.txt" << std::endl;
    }
    saveLog("Log file opened");
}

void closeLog(void)
{
    saveLog("Log file closed");
    logFile.close();
}

void saveLog(std::string msg)
{
    std::string ss;
    time_t currentTime = time(NULL);
    std::string txtTime = (std::string)asctime(localtime(&currentTime));
    txtTime = txtTime.substr(0, txtTime.length() - 1);
    ss = (std::string)"T: " + txtTime + " M: " + msg + "\n";
    logFile << ss.c_str();
    logFile.flush();
    std::cout << ss.c_str();
    std::cout.flush();
}