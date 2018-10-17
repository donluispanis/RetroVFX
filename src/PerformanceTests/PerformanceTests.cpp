#include "TestTemplate.h"

void voidF()
{
    return;
}

int main()
{

    float loopTime;
    float assignmentTime;

    bool showAssembler = false;

    TestTemplate T("bin/PerformanceResults.txt");

    T.WriteMessageIntoScreenAndFile("----------------------------------------------------\n|");
    T.WriteMessageIntoScreenAndFile("| Notice:  Each Test is averaged over a total of 100 tests repeated\n"
                                    "|          Inside every test, each operation is reapeated 10000000 times\n"
                                    "|          in order to be measurable in time\n|");

    T.ExecuteTest([]() {for (int j = 0; j < 10000000; j++); });
    loopTime = T.CalculateAverageTime();
    T.WriteTestResultsIntoScreenAndFile("01", "Void For Loop with I++", T.CalculateAverageTime());
    T.WriteMessageIntoScreenAndFile("| L15:\n|  cmpl	$9999999, -4(%ebp)\n|  jg	L16\n|  addl	$1, -4(%ebp)\n|  jmp	L15\n|\n|", showAssembler);

    T.ExecuteTest([]() {for (int j = 0; j < 10000000; ++j); });
    T.WriteTestResultsIntoScreenAndFile("02", "Void For Loop with ++I", T.CalculateAverageTime());
    T.WriteMessageIntoScreenAndFile("| L20:\n|  cmpl	$9999999, -4(%ebp)\n|  jg	L21\n|  addl	$1, -4(%ebp)\n|  jmp	L20\n|\n|", showAssembler);

    int i;
    T.ExecuteTest([&i]() {
        for (int j = 0; j < 10000000; ++j) {
            i = j;
    } });
    assignmentTime = T.CalculateAverageTime() - loopTime;
    T.WriteTestResultsIntoScreenAndFile("03", "Averaged cost of 2 MOVL - Simple assignment (=)", assignmentTime);
    T.WriteMessageIntoScreenAndFile("| L24:\n|  cmpl	$9999999, -4(%ebp)\n|  jg	L25\n|  movl	-4(%ebp), %eax\n|"
                                    "  movl	%eax, -8(%ebp)\n|  addl	$1, -4(%ebp)\n|  jmp	L24\n|\n|", showAssembler);

    T.ExecuteTest([]() {
        for (int j = 0; j < 10000000; ++j) {
            voidF();
    } });
    T.WriteTestResultsIntoScreenAndFile("04", "Cost of calling void function", T.CalculateAverageTime() - loopTime);
    T.WriteMessageIntoScreenAndFile("| L30:\n|  cmpl	$9999999, -4(%ebp)\n|  jg	L31\n|  call	__Z5voidFv\n|  addl	$1, -4(%ebp)\n|  jmp	L30\n|\n|", showAssembler);

    T.ExecuteTest([&i]() {
        for (int j = 0; j < 10000000; ++j) {
            i = rand();
    } });
    T.WriteTestResultsIntoScreenAndFile("05", "Cost of calling rand()", T.CalculateAverageTime() - loopTime - assignmentTime);
    T.WriteMessageIntoScreenAndFile("| L34:\n|  cmpl	$9999999, -12(%ebp)\n|  jg	L35\n|  movl	-28(%ebp), %eax\n|  movl	(%eax), %ebx"
                                    "\n|  call	_rand\n|  movl	%eax, (%ebx)\n|  addl	$1, -12(%ebp)\n|  jmp	L34\n|\n|", showAssembler);

    T.WriteMessageIntoScreenAndFile("----------------------------------------------------");

    return 0;
}