#include <chrono>
#include <fstream>
#include <functional>
#include <list>

class TestTemplate
{
  public:
    TestTemplate(const char* logPath);
    double CalculateAverageTime();
    void WriteTestResultsIntoScreenAndFile(const char *testName, const char *testDescription, double testTime);
    void WriteMessageIntoScreenAndFile(const char *message);
    void ExecuteTest(std::function<void(void)> test);

  private:
    std::streambuf *writeToScreen;
    std::filebuf *writeToFile;
    std::chrono::system_clock::time_point time_point;
    std::list<double> timeCounts;
    std::ofstream file;
};