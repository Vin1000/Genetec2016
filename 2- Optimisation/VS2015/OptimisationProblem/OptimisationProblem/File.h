#pragma once
#include <string>

class File
{
public:
    File() = default;
    File(const std::wstring folder, const std::wstring filename)
        : _folder(folder)
        , _filename(filename)
    {
    }
    ~File() = default;

    std::wstring Filename() const { return _filename; }
    std::wstring Folder() const { return _folder; }
    std::wstring FullPath() const { return _folder + _filename; }

    inline bool operator< (const File& rhs) const { return _filename < rhs._filename; }
    inline bool operator> (const File& rhs) const { return rhs._filename < _filename; }
    inline bool operator<=(const File& rhs) const { return !(_filename > rhs._filename); }
    inline bool operator>=(const File& rhs) const { return !(_filename < rhs._filename); }

private:
    std::wstring _folder;
    std::wstring _filename;
};

