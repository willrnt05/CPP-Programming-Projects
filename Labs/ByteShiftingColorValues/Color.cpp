#include <iostream>
#include <iomanip>
#include "Color.h"

using namespace std;

void Color::SetValue(int value)
{
    this->integerValue = value;
    this->blue = value & 0xFF;
    this->green = value >> 8 & 0xFF;
    this->red = value >> 16 & 0xFF;
}

void Color::SetName(const char* name)
{
    this->colorName = name;
}

//Probably wont work..... Have to do math and write loop
string Color::colorToHex(unsigned char color) const
{
    stringstream stream;
    stream << setfill('0') << setw(2) << hex << (int)color;
    string a = (stream.str());
    string b = "";
    for(char x : a){b+=toupper(x);}
    return b;
}

unsigned char Color::GetR() const{
    return this->red;
}
unsigned char Color::GetB() const{
    return this->blue;
}
unsigned char Color::GetG() const{
    return this->green;
}

string Color::GetHexValue() const {
    string a = "0x";
    a += colorToHex((int)this->red);
    a += colorToHex((int)this->green);
    a += colorToHex((int)this->blue);
    return a;
}

string Color::GetName() const
{
    return this->colorName;
}