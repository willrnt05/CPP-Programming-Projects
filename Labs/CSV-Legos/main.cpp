#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Data
{
    string setNumber;
    string theme;
    string setName;
    int minifigures;
    int numParts;
    double price;
};

void readUserData(const char* filePath, vector<Data>& _dataCollection)
{
    string fileDataTracker;
    int lineCount = 0;

    ifstream fileName(filePath);
    while (fileName.is_open() && !fileName.eof())
    {
        if(lineCount == 0)
        {
            getline(fileName, fileDataTracker);
            lineCount += 1;
        }
        else
        {
            Data tempData;

            string tempString;
            string numPartsString;
            string priceString;
            string stringMiniFigures;

            getline(fileName, tempString);
            istringstream stream(tempString);

            getline(stream, tempData.setNumber, ',');
            getline(stream, tempData.theme, ',');
            getline(stream, tempData.setName, ',');
            getline(stream, stringMiniFigures, ',');
            getline(stream, numPartsString, ',');
            getline(stream, priceString, ',');

            try {
                tempData.numParts = stoi(numPartsString);
                tempData.price = stod(priceString);
                tempData.minifigures = stoi(stringMiniFigures);
            }
            catch(invalid_argument &x) {
                tempData.numParts = 0;
                tempData.price = 0;
                tempData.minifigures = 0;
            }
            _dataCollection.push_back(tempData);
        }
    }
}

void printSet(Data set)
{
    cout << "Name: " << set.setName << endl <<
    "Number: " << set.setNumber << endl <<
    "Theme: " << set.theme << endl <<
    "Price: $" << set.price << endl <<
    "Minifigures: " << set.minifigures << endl <<
    "Piece count: " << set.numParts << endl;

}


int main()
{

    vector<Data> dataCollection;



    cout << std::fixed << setprecision(2);
    cout << "Which file(s) to open?\n";
    cout << "1. lego1.csv" << endl;
    cout << "2. lego2.csv" << endl;
    cout << "3. lego3.csv" << endl;
    cout << "4. All 3 files" << endl;
    int option;
    cin >> option;

    /*======= Load data from file(s) =======*/

    if (option == 1)
    {
        readUserData("lego1.csv", dataCollection);
    }
    else if(option == 2)
    {
        readUserData("lego2.csv", dataCollection);
    }
    else if(option == 3)
    {
        readUserData("lego3.csv", dataCollection);
    }
    else if(option == 4)
    {
        readUserData("lego1.csv", dataCollection);
        readUserData("lego2.csv", dataCollection);
        readUserData("lego3.csv", dataCollection);
    }


    cout << "1. Most Expensive set" << endl;
    cout << "2. Largest piece count" << endl;
    cout << "3. Search for set name containing..." << endl;
    cout << "4. Search themes..." << endl;
    cout << "5. Part count information" << endl;
    cout << "6. Price information" << endl;
    cout << "7. Minifigure information" << endl;
    cout << "8. If you bought one of everything..." << endl;
    cout << "0. Exit" << endl;

    int choice;
    cin >> choice;
    cin.get();  // Clear newline character for any later input

    /*======= Print out how many sets were loaded =======*/
    cout << "Total number of sets: " << dataCollection.size() << endl << endl;
    /*======= Based on the choice, execute the appropriate task and show the results =======*/
    if(choice == 1)
    {
        Data temp = dataCollection[0];
        for(unsigned int i = 1; i < dataCollection.size(); ++i)
        {
            if (dataCollection[i].price > temp.price)
            {
                temp = dataCollection[i];
            }
        }
        cout << "The most expensive set is: " << endl;
        printSet(temp);
    }
    else if(choice == 2)
    {
        Data temp = dataCollection[0];
        for(unsigned int i = 1; i < dataCollection.size(); ++i)
        {
            if (dataCollection[i].numParts > temp.numParts)
            {
                temp = dataCollection[i];
            }
        }
        cout << "The set with the highest parts count: " << endl;
        printSet(temp);
    }
    else if(choice == 3)
    {
        int numFound = 0;
        string tempName;
        getline(cin, tempName);

        for (unsigned int i = 0; i < dataCollection.size(); ++i) {
            Data a = dataCollection[i];
            if ((a.setName).find(tempName) != string::npos) {
                numFound += 1;
            }
        }
        if(numFound >= 1) {
            cout << "Sets matching \"" << tempName << "\":" << endl;
            for (unsigned int i = 0; i < dataCollection.size(); ++i) {
                Data a = dataCollection[i];
                if ((a.setName).find(tempName) != string::npos) {
                    cout << a.setNumber << " " << a.setName << " $" <<
                         a.price << endl;
                }
            }
        }
        else
        {
            cout << "No sets found matching that search term" << endl;
        }
    }
    else if(choice == 4)
    {
        string tempName;
        getline(cin, tempName);
        cout << "Sets matching \"" << tempName << "\":" << endl;
        for (unsigned int i = 0; i < dataCollection.size(); ++i)
        {
            Data a = dataCollection[i];
            if((a.theme).find(tempName) != string::npos)
            {
                cout << a.setNumber << " " << a.setName << " $" <<
                     a.price << endl;
            }
        }
    }
    else if(choice == 5)
    {
        int numPartsTotal = 0;
        for(Data a : dataCollection)
        {
            numPartsTotal += a.numParts;
        }
        int averagePartCount = (numPartsTotal) / dataCollection.size();

        cout << "Average part count for " << dataCollection.size()
        << " sets: " << averagePartCount << endl;
    }
    else if(choice == 6)
    {
        Data mostExpensive = dataCollection[0];
        Data leastExpensive = dataCollection[0];

        double priceTotal = 0;

        for(Data a : dataCollection)
        {
            if(a.price > mostExpensive.price)
            {
                mostExpensive = a;
            }
            if(a.price < leastExpensive.price)
            {
                leastExpensive = a;
            }
            priceTotal += a.price;
        }
        double averagePrice = (priceTotal) / ((double)dataCollection.size());

        cout << "Average price for " << dataCollection.size()
             << " sets: $" << averagePrice << endl;

        cout << "Least expensive set: " << endl;
        printSet(leastExpensive);

        cout << "Most expensive set: " << endl;
        printSet(mostExpensive);
    }
    else if(choice == 7)
    {
        double averageMinifigures = 0;
        Data mostMiniFigures = dataCollection[0];

        for(Data a : dataCollection)
        {
            averageMinifigures += a.minifigures;
            if(a.minifigures > mostMiniFigures.minifigures)
            {
                mostMiniFigures = a;
            }
        }
        cout << "Average number of minifigures: " <<
        (int)averageMinifigures / dataCollection.size() << endl;

        cout << "Set with the most minifigures: " << endl;
        printSet(mostMiniFigures);
    }
    else if(choice == 8)
    {
        double totalCost = 0;
        int totalPieces = 0;
        int totalMiniFigures = 0;
        for(Data i : dataCollection)
        {
            totalCost += i.price;
            totalMiniFigures += i.minifigures;
            totalPieces += i.numParts;
        }
        cout << "If you bought one of everything..." << endl <<
        "It would cost: $" << totalCost << endl << "You would have " <<
        totalPieces << " pieces in your collection" << endl <<
        "You would have an army of " << totalMiniFigures << " minifigures!" << endl;
    }
    return 0;
}
