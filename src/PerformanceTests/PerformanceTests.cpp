#include "TestTemplate.h"

int main()
{
    TestTemplate T("bin/PerformanceResults.txt");

    T.WriteMessageIntoScreenAndFile("----------------------------------------------------\n|");

    T.ExecuteTest([]() {for (int j = 0; j < 10000000; j++); });
    T.WriteTestResultsIntoScreenAndFile("01", "Void For Loop with I++", T.CalculateAverageTime());

    T.ExecuteTest([]() {for (int j = 0; j < 10000000; ++j); });
    T.WriteTestResultsIntoScreenAndFile("02", "Void For Loop with ++I", T.CalculateAverageTime());

    T.WriteMessageIntoScreenAndFile("----------------------------------------------------");

    return 0;
}