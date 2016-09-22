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
    std::string log;

    Logger::Info(std::string("Last error code: ") + std::to_string(GetLastError()));

    if (_hFind != INVALID_HANDLE_VALUE)
    {
        Logger::Info("Closing previous directory.");
        FindClose(_hFind);
        _hFind = INVALID_HANDLE_VALUE;
        _ffd = WIN32_FIND_DATAW();
    }

    Logger::Info(std::string("Last error code: ") + std::to_string(GetLastError()));

    log = "Verifying path: ";
    if (pFolderPath == nullptr)
    {
        Logger::Info(log + "Invalid");
        return INVALID_ARGUMENTS;
    }
    Logger::Info(log + "Valid");

    _path = s2ws(pFolderPath);

    if (0 == _path.length())
    {
        Logger::Info("Did not convert any characters :(");
        return INVALID_ARGUMENTS;
    }

    std::wstring search = _path + s2ws("*");

    if (_path.length() >= MAX_PATH)
    {
        Logger::Error("Path received is too long to be a valid path.");
        return INVALID_ARGUMENTS;
    }

    log = "Opening directory: ";

    _hFind = FindFirstFileW(search.c_str(), &_ffd);

    Logger::Info(std::string("Last error code: ") + std::to_string(GetLastError()));

    auto lastError = GetLastError();
    Logger::Info(log + (_hFind == INVALID_HANDLE_VALUE ? "Failed." : "Success."));
    if (lastError != ERROR_SUCCESS)
    {
        Logger::Error("FindFirstFileW returned error code:" + std::to_string(lastError));
    }

    return OK;
}

std::list<File> Directory::Files()
{
    using std::cout;
    using std::begin;
    using std::end;
    using std::endl;
    using std::wstring;

    std::string log;
    std::list<File> files;

    log = "Checking if directory handle is valid: ";

    // Did we successfully open the folder and is there a file present
    if (_hFind == INVALID_HANDLE_VALUE)
    {
        Logger::Warning(log + "Invalid.");
        return files;
    }

    Logger::Info(log + "Valid.");
    Logger::Info("Checking files contained in the folder.");

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

    Logger::Info("Found " + std::to_string(files.size()) + " file(s) in the folder.");

    return files;
}