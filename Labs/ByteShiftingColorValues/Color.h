#pragma once
#include <string>
#include<iomanip>

using namespace std;

class Color
{
public:
    string colorName;
    int integerValue;
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    string colorToHex(unsigned char color) const;
    void SetValue(int value);
    void SetName(const char* name);

    unsigned char GetR() const;
    unsigned char GetG() const;
    unsigned char GetB() const;

    string GetHexValue() const;
    string GetName() const;
};