#pragma once

class FileLoader
{
  public:
    static bool OpenBinaryFile(const char *path, unsigned char *&output, unsigned int &size);
    static void CloseBinaryFile(unsigned char *output);
};