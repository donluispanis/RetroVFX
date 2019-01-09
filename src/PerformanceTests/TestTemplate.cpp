#include <iostream>
#include <list>
#include <numeric>
#include <cmath>

#include "TestTemplate.h"

TestTemplate::TestTemplate(const char *logPath)
{
    std::cout << std::endl;
    std::cout << "Running tests... this may take a while" << std::endl;
    std::cout << "Output will be stored in " << logPath << std::endl;
    std::cout << std::endl;

    file = std::ofstream(logPath);
    writeToScreen = std::cout.rdbuf();
    writeToFile = file.rdbuf();
}

void TestTemplate::ExecuteTest(std::function<void(void)> test)
{
    timeCounts.clear();
    std::chrono::duration<double> elapsedSeconds;

    for (int i = 0; i < 100; i++)
    {
        time_point = std::chrono::system_clock::now();

        test();

        elapsedSeconds = std::chrono::system_clock::now() - time_point;
        timeCounts.push_back(elapsedSeconds.count());
    }
}

double TestTemplate::CalculateAverageTime()
{
    double time = std::accumulate(timeCounts.begin(), timeCounts.end(), 0.0) / (double)timeCounts.size();
    return time;
}

void TestTemplate::WriteTestResultsIntoScreenAndFile(const char *testName, const char *testDescription, double testTime)
{
    auto output = [](const char *testName, const char *testDescription, double testTime) {
        std::cout << "| Test " << testName << ": " << testDescription << std::endl;
        std::cout << "|          Time spent: " << testTime << " seconds" << std::endl;
        std::cout << "|" << std::endl;
    };

    std::cout.rdbuf(writeToFile);
    output(testName, testDescription, testTime);

    std::cout.rdbuf(writeToScreen);
    output(testName, testDescription, testTime);
}

void TestTemplate::WriteMessageIntoScreenAndFile(const char *message, bool write)
{
    if (write)
    {
        std::cout.rdbuf(writeToFile);
        std::cout << message << std::endl;

        std::cout.rdbuf(writeToScreen);
        std::cout << message << std::endl;
    }
}