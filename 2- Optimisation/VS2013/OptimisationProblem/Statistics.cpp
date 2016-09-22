#include "stdafx.h"
#include "Statistics.h"
#include "FileReader.h"
#include "Logger.h"
#include "HelperMethods.h"

Statistics::Statistics(char c)
{
    _character = c;
    _index = 0;
    _arraySize = 5;
    _characterOccurences = new int[_arraySize];
    _characterRatio      = new float[_arraySize];
    for (int C = 0; C < 5; C++)
    {
        switch (C)
        {
        case 0:
            _characterOccurences[0] = 0;
            _characterRatio[0] = 0;
        case 1:
            _characterOccurences[1] = 0;
            _characterRatio[1] = 0;
        case 2:
            _characterOccurences[2] = 0;
            _characterRatio[2] = 0;
        case 3:
            _characterOccurences[3] = 0;
            _characterRatio[3] = 0;
        case 4:
            _characterOccurences[4] = 0;
            _characterRatio[4] = 0;
        }
    }
}

Statistics::~Statistics()
{
    //TODO: Remove the toto, i know this leaks
    delete _characterOccurences;
    delete _characterRatio;
}

int Statistics::ComputeCharacterAverageOccurences() const
{
    int total = 0;
    for (int i = 0; i < _index; i++)
    {
        total = total + _characterOccurences[i];
    }

    if (total > 0)
        return total / (_index + 1);

    return 0;
}
float Statistics::ComputeCharacterAverageRatio() const
{
    float total = 0;
    for (int i = 0; i < _index; i++)
    {
        total = total + _characterRatio[i];
    }

    if (total > 0)
        return total / (_index + 1);

    return 0.0f;
}



std::string Statistics::ComputeFile(FileReader fr, std::wstring fileName)
{
    
    if (_index == _arraySize)
    {
        Resize(_characterOccurences, _index);
        Resize(_characterRatio, _index);
        _arraySize = _arraySize + VECTOR_RESIZE_VALUE;
    }

    int totalCharCount = 0;
    while (!fr.IsEOF())
    {
        std::string line;
        if (fr.ReadLine(line))
        {
            totalCharCount += (int)line.size();
            for (std::string::size_type i = 0; i < line.size(); ++i)
            {
                char c = line[i];
                if (c == _character)
                {
                    _characterOccurences[_index] = _characterOccurences[_index] + 1;
                }
            }
        }
    }

    if(totalCharCount!= 0)
        _characterRatio[_index] =  ((float)_characterOccurences[_index] / (float)totalCharCount) * 100.0f;

    //do not modify this string as we will later use the fileName to re-order the stats.txt file
    std::string output = ws2s(fileName) + " : " + std::to_string(_characterOccurences[_index]) + " occurence of:" + std::string(1, _character) + " representing " + std::to_string(_characterRatio[_index]) + "%";

    _index++;

    return output;
}

template <class T>
void Statistics::Resize(T*& array, size_t currentSize) const
{
    T* tempArray = new T[currentSize+VECTOR_RESIZE_VALUE];
    for (int i = 0; i < currentSize; i++)
    {
        tempArray[i] = array[i];
    }
    delete[] array;
    array = tempArray;

    for (size_t i = currentSize; i < currentSize + VECTOR_RESIZE_VALUE; i++)
    {
        array[i] = 0;
    }
}
