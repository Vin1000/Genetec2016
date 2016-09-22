#include "stdafx.h"
#include "Statistics.h"
#include "FileReader.h"
#include "Logger.h"
#include "HelperMethods.h"

Statistics::Statistics(char c, int size)
{
    _character = c;
    _index = 0;
    _arraySize = size;
    _characterOccurences = new int[_arraySize];
    _characterRatio      = new float[_arraySize];
    for (int C = 0; C < size; C++)
    {
        _characterOccurences[C] = 0;
        _characterRatio[C] = 0;
    }
}

Statistics::~Statistics()
{
    //TODO: Remove the toto, i know this leaks
    delete _characterOccurences;
    delete _characterRatio;
}

std::string Statistics::ComputeFile(FileReader fr, std::wstring fileName)
{
    int totalCharCount = 0;
	int occurences = 0;

	std::string line;
    while (fr.ReadLine(line))
    {
		int lineSize = line.size();
        totalCharCount += (int)lineSize;
        for (std::string::size_type i = 0; i < lineSize; ++i)
        {
            if (line[i] == _character)
            {
				occurences++;
            }
        }
    }

	_characterOccurences[_index] = occurences;

    if(totalCharCount!= 0)
        _characterRatio[_index] =  ((float)_characterOccurences[_index] / (float)totalCharCount) * 100.0f;

    //do not modify this string as we will later use the fileName to re-order the stats.txt file
    std::string output = ws2s(fileName) + " : " + std::to_string(_characterOccurences[_index]) + " occurence of:" + std::string(1, _character) + " representing " + std::to_string(_characterRatio[_index]) + "%";

    _index++;

    return output;
}
