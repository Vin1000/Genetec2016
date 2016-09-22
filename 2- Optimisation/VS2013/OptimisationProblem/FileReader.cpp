#include "stdafx.h"
#include "FileReader.h"


FileReader::FileReader()
{
}


FileReader::~FileReader()
{
    _fr.close();
}

bool FileReader::Open(std::wstring filename)
{
    _fr.close();
    _fr.open(filename, std::ios::in);
    return _fr.is_open();
}

bool FileReader::ReadLine(std::string &line)
{
    if (_fr.is_open() && !_fr.eof())
    {
        std::getline(_fr, line);
        return true;
    }
    return false;
}