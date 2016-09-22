#pragma once

#include <vector>

class Encoder
{
public:
    std::string EncodeString(const std::string input);
private:
    std::string base64Encode(std::vector<BYTE> inputBuffer);
};