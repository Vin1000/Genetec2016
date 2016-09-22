#pragma once
#include <fstream>

class FileWriter
{
public:
    FileWriter();
    virtual ~FileWriter();

    bool Open(std::string path, bool fAppend = true, bool fEncodeData = false);
    void Write(std::string s);

private:
    std::ofstream _fs;
    bool _encode;
};

