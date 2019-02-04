#include "FileLoader.h"
#include <fstream>

void FileLoader::OpenBinaryFile(const char *path, unsigned char *&output, unsigned int &size)
{
    std::ifstream input(path, std::ios::binary);

    input.seekg(0, input.end); //Point to the end of the file to be able to measure the size
    int fileSize = input.tellg();
    input.seekg(0, input.beg); //Point back to the beginning of the file

    char *buffer = new char[fileSize];
    input.rdbuf()->sgetn(buffer, fileSize); //Copy contents of the file into a buffer

    output = (unsigned char *)buffer;
    size = fileSize;
}

void FileLoader::CloseBinaryFile(unsigned char *output)
{
    delete [] output;
}