#include "stdafx.h"
#include "Logger.h"
#include "Encoder.h"

const static TCHAR encodeLookup[] = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
const static TCHAR padCharacter = TEXT('=');

std::string Encoder::EncodeString(const std::string input)
{
    std::vector<BYTE> inputBuffer;

    for (int i = 0; i < input.size(); i++)
    {
        inputBuffer.push_back(input[i]);
    }
   
    return base64Encode(inputBuffer);
}


std::string Encoder::base64Encode(std::vector<BYTE> inputBuffer)
{
    std::string encodedString;
    encodedString.reserve(((inputBuffer.size() / 3) + (inputBuffer.size() % 3 > 0)) * 4);
    DWORD temp;
    std::vector<BYTE>::iterator cursor = inputBuffer.begin();
    for (size_t idx = 0; idx < inputBuffer.size() / 3; idx++)
    {
        temp = (*cursor++) << 16; //Convert to big endian
        temp += (*cursor++) << 8;
        temp += (*cursor++);
        encodedString.append(1, encodeLookup[(temp & 0x00FC0000) >> 18]);
        encodedString.append(1, encodeLookup[(temp & 0x0003F000) >> 12]);
        encodedString.append(1, encodeLookup[(temp & 0x00000FC0) >> 6]);
        encodedString.append(1, encodeLookup[(temp & 0x0000003F)]);
    }
    switch (inputBuffer.size() % 3)
    {
    case 1:
        temp = (*cursor++) << 16; //Convert to big endian
        encodedString.append(1, encodeLookup[(temp & 0x00FC0000) >> 18]);
        encodedString.append(1, encodeLookup[(temp & 0x0003F000) >> 12]);
        encodedString.append(2, padCharacter);
        break;
    case 2:
        temp = (*cursor++) << 16; //Convert to big endian
        temp += (*cursor++) << 8;
        encodedString.append(1, encodeLookup[(temp & 0x00FC0000) >> 18]);
        encodedString.append(1, encodeLookup[(temp & 0x0003F000) >> 12]);
        encodedString.append(1, encodeLookup[(temp & 0x00000FC0) >> 6]);
        encodedString.append(1, padCharacter);
        break;
    }
    return encodedString;
}