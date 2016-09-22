#pragma once
#include <fstream>
#include <string>

class FileReader
{
public:
    FileReader();
    FileReader(FileReader&&o) { std::swap(_fr, o._fr); }
    virtual ~FileReader();

    bool Open(std::wstring filename);
    bool ReadLine(std::string &line);
    bool IsEOF() const { return _fr.eof(); }

    FileReader& operator=(const FileReader&) = delete;

private:
    FileReader(const FileReader &);

private:
    std::fstream _fr;
};

