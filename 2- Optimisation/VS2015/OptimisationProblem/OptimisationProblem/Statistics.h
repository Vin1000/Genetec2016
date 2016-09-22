#pragma once

#include <string>
#include "FileReader.h"

class Statistics
{
private:
    char   _character;
    //Keep track of the occurences of a specific character in this array, pos 1 = number of occurence in 1st file.
    int*   _characterOccurences;
    //Keep track of the % of occurences over all the character in a file
    float* _characterRatio;

    mutable int _arraySize;
    int _index;
public:
    Statistics(char c);
    ~Statistics();

    std::string ComputeFile(FileReader fr, std::wstring fileName);
    int ComputeCharacterAverageOccurences() const;
    float ComputeCharacterAverageRatio() const;

    template<class T>
    void Resize(T*& array, size_t currentSize) const;
};
