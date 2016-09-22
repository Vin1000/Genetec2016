#include "stdafx.h"
#include "FileWriter.h"


#include <string>
#include"Encoder.h"

FileWriter::FileWriter()
{
    _encode = false;
}

FileWriter::~FileWriter()
{
    _fs.close();
}

bool FileWriter::Open(std::string path, bool fAppend, bool fEncodeData)
{
    _encode = fEncodeData;
    _fs.close();
    if (fAppend)
        _fs.open(path, std::ofstream::app);
    else
        _fs.open(path);

    return _fs.is_open();
}

void FileWriter::Write(std::string s)
{
    Encoder enc;
    std::string s_enc = enc.EncodeString(s);
    if (_fs.is_open())
    {
        _fs << (_encode? s_enc:s) << std::endl;
    }
}
