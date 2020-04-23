#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "Color.h"
using namespace std;

void ReadFile(const char* filename,  map<string, Color>& colors);
void PrintColors(const map<string, Color>& colors);
void PrintColor(const Color& color);
void SearchForColor(map<string, Color>& colors);


int main()
{
    cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
    cout << "7. Load all 6 files" << endl;
    int choice;
    cin >> choice;

    map<string, Color> colors;
    if (choice >= 1 && choice <= 6)
    {
        string file = "colors" + to_string(choice) + ".txt";
        ReadFile(file.c_str(), colors);
    }
    else if (choice == 7)
    {
        for (int i = 1; i <= 6; i++)
        {
            string file = "colors" + to_string(i) + ".txt";
            ReadFile(file.c_str(), colors);
        }

    }

    // Secondary menu
    cout << "1. Show all colors" << endl;
    cout << "2. Search for a color" << endl;
    cin >> choice;

    if (choice == 1)
        PrintColors(colors);
    else if (choice == 2)
        SearchForColor(colors);
    return 0;
}

void ReadFile(const char* filename, map<string, Color>& colors)
{
    ifstream file(filename);

    while(!file.eof())
    {
        Color tempColor;

        string colorInteger;
        string colorName;

        string tempString;
        getline(file, tempString);

        istringstream stream(tempString);

        getline(stream, colorName, ' ');
        getline(stream, colorInteger, ' ');

        try{
            tempColor.SetName(colorName.c_str());
            tempColor.SetValue(stoi(colorInteger));
        }
        catch(invalid_argument &x){
            break;
        }

        colors[colorName] = tempColor;
    }
}
void PrintColors(const map<string, Color>& colors)
{
    int numColors = 0;
    auto iter = colors.begin();
    for(; iter != colors.end(); ++iter)
    {
        cout << iter->second.colorName << " " <<
        iter->second.GetHexValue() <<
        " " << (int)iter->second.red
        << "," << (int)iter->second.green << "," << (int)iter->second.blue << endl;
        //cout << "Made through print" << endl;
        numColors += 1;
    }
    cout << "Number of colors: " << numColors << endl;
}
void PrintColor(const Color& color)
{
    cout << left << setw(20) << color.GetName();
    cout << right << setw(10) << color.GetHexValue();
    cout << "\t\t" << (int)color.GetR() << "," << (int)color.GetG() << "," << (int)color.GetB() << endl;
}
void SearchForColor(map<string, Color>& colors)
{
    string colorName;
    cin >> colorName;
    bool found = false;
    auto iter = colors.begin();
    for(; iter != colors.end(); ++iter)
    {
        if (iter->first == colorName) {
            cout << iter->second.colorName << " " << iter->second.GetHexValue() << " " << (int)iter->second.red
                 << "," << (int)iter->second.green << "," << (int)iter->second.blue << endl;
            found = true;
        }
    }
    if (found == false)
    {
        cout << colorName << " not found!" << endl;
    }
}
