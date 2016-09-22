#include "stdafx.h"
#include "Directory.h"

#include "Logger.h"
#include "HelperMethods.h"

#include <algorithm>
#include <iostream>
#include <vector>

Directory::Directory()
    : _hFind(INVALID_HANDLE_VALUE)
{
}


Directory::~Directory()
{
    if (_hFind != INVALID_HANDLE_VALUE)
    {
        FindClose(_hFind);
    }
}

///
// pFolderPath: Path to a folder
// return: STATUS_CODE
///
STATUS_CODE Directory::Open(char const *pFolderPath)
{
    using std::min;

    if (_hFind != INVALID_HANDLE_VALUE)
    {
        FindClose(_hFind);
        _hFind = INVALID_HANDLE_VALUE;
        _ffd = WIN32_FIND_DATAW();
    }


    if (pFolderPath == nullptr)
    {
        return INVALID_ARGUMENTS;
    }

    _path = s2ws(pFolderPath);

    if (0 == _path.length())
    {
        return INVALID_ARGUMENTS;
    }

    std::wstring search = _path + s2ws("*");

    if (_path.length() >= MAX_PATH)
    {
        return INVALID_ARGUMENTS;
    }


    _hFind = FindFirstFileW(search.c_str(), &_ffd);
	
    auto lastError = GetLastError();

    return OK;
}

std::list<File> Directory::Files()
{
    using std::cout;
    using std::begin;
    using std::end;
    using std::endl;
    using std::wstring;

    std::list<File> files;


    // Did we successfully open the folder and is there a file present
    if (_hFind == INVALID_HANDLE_VALUE)
    {
        return files;
    }
	
    // Get list of files in the folder
    std::vector<File> v(0);
    do
    {

        if (!(_ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            //Logger::Info("Found a file.");

            if (v.capacity() < 0)
                v.resize(VECTOR_RESIZE_VALUE);

            File f(_path, _ffd.cFileName);

            v.push_back(f);
        }
    } while (FindNextFileW(_hFind, &_ffd) != 0);

    // copy vector to list
    for (unsigned i = 0; i<v.size(); i++) files.push_back(v[i]);
	
    return files;
}