#pragma once
#include "File.h"
#include <list>

enum STATUS_CODE
{
    OK,
    INVALID_ARGUMENTS,
};

class Directory
{
public:
    Directory();
    ~Directory();

    STATUS_CODE Open(char const *pFolderPath);

    std::list<File> Files();

private:
    WIN32_FIND_DATAW _ffd;
    HANDLE _hFind;
    std::wstring _path;
};

