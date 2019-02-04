#include "FileLoader.h"
#include <fstream>

void FileLoader::LoadBinaryFile(const char *path, unsigned char *&output, unsigned int &size)
{
    std::ifstream input(path, std::ios::binary );

    input.seekg(0, input.end);
    int fileSize = input.tellg();
    input.seekg(0, input.beg);

    char *buffer = new char[fileSize];
    input.rdbuf()->sgetn(buffer, fileSize);

    output = (unsigned char *)buffer;
    size = fileSize;
}