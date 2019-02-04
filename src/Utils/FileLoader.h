#pragma once

class FileLoader
{
  public:
    static void LoadBinaryFile(const char *path, unsigned char *&output, unsigned int &size);
};