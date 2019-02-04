#pragma once

class FileLoader
{
  public:
    static void OpenBinaryFile(const char *path, unsigned char *&output, unsigned int &size);
    static void CloseBinaryFile(unsigned char *output);
};