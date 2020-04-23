#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>


using namespace std;

struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct Image
{
    Header H;
    vector<Pixel> allPixels; //Bottom left => Bottom Right => Top
};

void copyHeader(Image& A, Image& B)
{
    A.H.idLength = B.H.idLength;
    A.H.dataTypeCode = B.H.dataTypeCode;
    A.H.colorMapOrigin = B.H.colorMapOrigin;
    A.H.colorMapLength = B.H.colorMapLength;
    A.H.colorMapDepth = B.H.colorMapDepth;
    A.H.xOrigin = B.H.xOrigin;
    A.H.yOrigin = B.H.yOrigin;
    A.H.width = B.H.width;
    A.H.height = B.H.height;
    A.H.bitsPerPixel = B.H.bitsPerPixel;
    A.H.imageDescriptor = B.H.imageDescriptor;
}

void printHeader(Image I)
{
    cout << "ID Length: " << (int)I.H.idLength << endl;
    cout << "Color Map Type: " << (int)I.H.colorMapType << endl;
    cout << "Data type code: " << (int)I.H.dataTypeCode << endl;
    cout << "Color Map Origin: " << (int)I.H.colorMapOrigin << endl;
    cout << "Color Map Length: " << (int)I.H.colorMapLength << endl;
    cout << "Color Map Depth: " << (int)I.H.colorMapDepth << endl;
    cout << "X Origin: " << (int)I.H.xOrigin << endl;
    cout << "Y Origin: " << (int)I.H.yOrigin << endl;
    cout << "Width: " << (int)I.H.width << endl;
    cout << "Height: " << (int)I.H.height << endl;
    cout << "Bits per pixel: " << (int)I.H.bitsPerPixel << endl;
    cout << "Image Descriptor: " << (int)I.H.imageDescriptor << endl;
}

void WriteBinaryFile(string fileName, Image A)
{
    ofstream fileX(fileName, ios_base::binary);

    //Header imageHeader;
    fileX.write((char*)&(A.H.idLength), 1);
    fileX.write((char*)&(A.H.colorMapType), 1);
    fileX.write((char*)&(A.H.dataTypeCode), 1);
    fileX.write((char*)&(A.H.colorMapOrigin), 2);
    fileX.write((char*)&(A.H.colorMapLength), 2);
    fileX.write((char*)&(A.H.colorMapDepth), 1);
    fileX.write((char*)&(A.H.xOrigin), 2);
    fileX.write((char*)&(A.H.yOrigin), 2);
    fileX.write((char*)&(A.H.width), 2);
    fileX.write((char*)&(A.H.height), 2);
    fileX.write((char*)&(A.H.bitsPerPixel), 1);
    fileX.write((char*)&(A.H.imageDescriptor), 1);

    //tempImage.H = imageHeader;

    int numPixels = A.H.width * A.H.height;

    for (int i = 0; i < numPixels; ++i)
    {
        fileX.write((char *)&(A.allPixels[i].blue), 1);
        fileX.write((char *)&(A.allPixels[i].green), 1);
        fileX.write((char *)&(A.allPixels[i].red), 1);
    }
}

//Return image, get rid of array
Image ReadBinaryFile(string fileName) {
    ifstream fileX(fileName, ios_base::binary);
    Image tempImage;
    //Header imageHeader;
    fileX.read((char*)&(tempImage.H.idLength), 1);
    fileX.read((char*)&(tempImage.H.colorMapType), 1);
    fileX.read((char*)&(tempImage.H.dataTypeCode), 1);
    fileX.read((char*)&(tempImage.H.colorMapOrigin), 2);
    fileX.read((char*)&(tempImage.H.colorMapLength), 2);
    fileX.read((char*)&(tempImage.H.colorMapDepth), 1);
    fileX.read((char*)&(tempImage.H.xOrigin), 2);
    fileX.read((char*)&(tempImage.H.yOrigin), 2);
    fileX.read((char*)&(tempImage.H.width), 2);
    fileX.read((char*)&(tempImage.H.height), 2);
    fileX.read((char*)&(tempImage.H.bitsPerPixel), 1);
    fileX.read((char*)&(tempImage.H.imageDescriptor), 1);

    //tempImage.H = imageHeader;

    int numPixels = tempImage.H.width * tempImage.H.height;

    for (int i = 0; i < numPixels; ++i)
    {
        Pixel tempPixel;
        fileX.read((char *)&(tempPixel.blue), 1);
        fileX.read((char *)&(tempPixel.green), 1);
        fileX.read((char *)&(tempPixel.red), 1);
        tempImage.allPixels.push_back(tempPixel);
    }
    return tempImage;
}

//Need Multiply, Subtract, Screen, Overlay
//Need to bind all functions less than 255
//Solve Multiply problem first
//Setall Headers to any Image.


Image Multiply(Image A, Image B)
{
    Image finalImage;
    copyHeader(finalImage, A);
    for(int i = 0; i < A.allPixels.size(); ++i)
    {
        Pixel tempPixel;

        tempPixel.blue = (((A.allPixels[i].blue * B.allPixels[i].blue) / 255.0f) + 0.5f);
        tempPixel.red  = (((A.allPixels[i].red * B.allPixels[i].red) /255.0f) + 0.5f);
        tempPixel.green = (((A.allPixels[i].green * B.allPixels[i].green) / 255.0f) + 0.5f);

        finalImage.allPixels.push_back(tempPixel);
    }
    return finalImage;
}
//A is Bottom, B is Top
Image Screen(Image A, Image B)
{
    Image finalImage;
    copyHeader(finalImage, A);
    for(int i = 0; i < A.allPixels.size(); ++i)
    {
        Pixel tempPixel;

        float redA = A.allPixels[i].red / 255.0f;
        float blueA = A.allPixels[i].blue / 255.0f;
        float greenA = A.allPixels[i].green / 255.0f;

        float redB = B.allPixels[i].red / 255.0f;
        float blueB = B.allPixels[i].blue / 255.0f;
        float greenB = B.allPixels[i].green / 255.0f;

        tempPixel.red = (1 - ((1 - redA) * (1 - redB))) * 255 + 0.5f;
        tempPixel.green = (1 - ((1 - greenA) * (1 - greenB))) * 255 + 0.5f;
        tempPixel.blue = (1 - ((1 - blueA) * (1 - blueB))) * 255 + 0.5f;

        finalImage.allPixels.push_back(tempPixel);
    }
    return finalImage;
}
//A is Bottom Layer, B is Top Layer
Image Subtract(Image A, Image B)
{

    Image finalImage;
    copyHeader(finalImage, A);
    for(int i = 0; i < A.allPixels.size(); ++i)
    {
        Pixel tempPixel;

        int redA = A.allPixels[i].red;
        int blueA = A.allPixels[i].blue;
        int greenA = A.allPixels[i].green;

        int redB = B.allPixels[i].red;
        int blueB = B.allPixels[i].blue;
        int greenB = B.allPixels[i].green;

        int red = redA - redB;
        int blue = blueA - blueB;
        int green = greenA - greenB;


        if (red < 0)
        {
            red = 0;
        }

        if (green < 0)
        {
            green = 0;
        }

        if (blue < 0)
        {
            blue = 0;
        }

        tempPixel.red = red;
        tempPixel.green = green;
        tempPixel.blue = blue;
        finalImage.allPixels.push_back(tempPixel);
    }
    return finalImage;
}

Image Overlay(Image A, Image B)
{
    Image finalImage1;
    copyHeader(finalImage1, A);

    for(int i = 0; i < A.allPixels.size(); ++i)
    {
        Pixel finalImage;
        float redA = A.allPixels[i].red / 255.0f;
        float blueA = A.allPixels[i].blue / 255.0f;
        float greenA = A.allPixels[i].green / 255.0f;

        float redB = B.allPixels[i].red / 255.0f;
        float blueB = B.allPixels[i].blue / 255.0f;
        float greenB = B.allPixels[i].green / 255.0f;

        if (redB <= 0.5)
        {
            finalImage.red = (2 * redA * redB) * 255 + 0.5f;
        }
        else
        {
            finalImage.red = (1 - (2 * (1 - redA) * (1 - redB))) * 255 + 0.5f;
        }
        if (greenB <= 0.5)
        {
            finalImage.green = (2 * greenA * greenB) * 255 + 0.5f;
        }
        else
        {
            finalImage.green = (1 - (2 * (1 - greenA) * (1 - greenB))) * 255 + 0.5f;
        }
        if (blueB <= 0.5)
        {
            finalImage.blue = (2 * blueA * blueB) * 255 + 0.5f;
        }
        else
        {
            finalImage.blue = (1 - (2 * (1 - blueA) * (1 - blueB))) * 255 + 0.5f;
        }
        finalImage1.allPixels.push_back(finalImage);
    }
    return finalImage1;
}

Image ExtraCredit(Image A, Image B, Image C, Image D) {
    Image finalImage;
    copyHeader(finalImage, A);

    finalImage.H.width = A.H.width * 2;
    finalImage.H.height = A.H.height * 2;


    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < A.H.height; ++i)
    {
        for (int j = 0; j < A.H.width; ++j)
        {
            finalImage.allPixels.push_back(A.allPixels[index1]);
            index1 += 1;
        }
        for (int j = 0; j < B.H.width; ++j)
        {
            finalImage.allPixels.push_back(B.allPixels[index2]);
            index2 += 1;
        }
    }
    index1 = 0;
    index2 = 0;
    for (int i = 0; i < C.H.height; ++i)
    {
        for (int j = 0; j < C.H.width; ++j)
        {
            finalImage.allPixels.push_back(C.allPixels[index1]);
            index1 += 1;
        }
        for (int j = 0; j < D.H.width; ++j)
        {
            finalImage.allPixels.push_back(D.allPixels[index2]);
            index2 += 1;
        }
    }
    return finalImage;
}


//Check header also
void compareImage(Image A, Image B)
{
    if(A.H.idLength != B.H.idLength||
    A.H.dataTypeCode != B.H.dataTypeCode||
    A.H.colorMapOrigin != B.H.colorMapOrigin||
    A.H.colorMapLength != B.H.colorMapLength||
    A.H.colorMapDepth != B.H.colorMapDepth||
    A.H.xOrigin != B.H.xOrigin||
    A.H.yOrigin != B.H.yOrigin||
    A.H.width != B.H.width||
    A.H.height != B.H.height||
    A.H.bitsPerPixel != B.H.bitsPerPixel||
    A.H.imageDescriptor != B.H.imageDescriptor)
    {
        cout <<"The Headers do not match.. " << endl;
        printHeader(A);
        printHeader(B);
        return;
    }


    if(A.allPixels.size() != B.allPixels.size())
    {
        cout << "Not matching size "  << endl;
        return;
    }

    for(int i = 0; i < A.allPixels.size(); ++i)
    {
       //cout << "A Blue: " << (int)A.allPixels[i].blue << endl;
       //cout << "B Blue: " << (int)B.allPixels[i].blue << endl;

       //cout << "A Green: " << (int)A.allPixels[i].green << endl;
       //cout << "B Green: " << (int)B.allPixels[i].green << endl;

       //cout << "A Red: " << (int)A.allPixels[i].red << endl;
       //cout << "B Red: " << (int)B.allPixels[i].red << endl;

        if((A.allPixels[i].blue != B.allPixels[i].blue)
        || (A.allPixels[i].green != B.allPixels[i].green)
        || (A.allPixels[i].red != B.allPixels[i].red))
        {
            cout << i << endl;
            cout << "A Blue: " << (int)A.allPixels[i].blue << endl;
            cout << "B Blue: " << (int)B.allPixels[i].blue << endl;

            cout << "A Green: " << (int)A.allPixels[i].green << endl;
            cout << "B Green: " << (int)B.allPixels[i].green << endl;

            cout << "A Red: " << (int)A.allPixels[i].red << endl;
            cout << "B Red: " << (int)B.allPixels[i].red << endl;
            cout << "Test Failed!" << endl;
            return;
        }
    }
    cout << "Test Passed!" << endl;
}


int main()
{
    //Part 1
    Image layer1 = ReadBinaryFile("input/layer1.tga");
    Image pattern1 = ReadBinaryFile("input/pattern1.tga");
    //Image part1Example = ReadBinaryFile("src/test/EXAMPLE_part1.tga");
    Image test1Image = Multiply(layer1, pattern1);
    WriteBinaryFile("output/part1.tga", test1Image);
    //cout << "Part 1 Testing..... ";
    //compareImage(test1Image, part1Example);

    //Part 2
    Image layer2 = ReadBinaryFile("input/layer2.tga");
    Image car = ReadBinaryFile("input/car.tga");
    //Image part2Example = ReadBinaryFile("src/test/EXAMPLE_part2.tga");
    Image test2Image = Subtract(car, layer2);
    //printHeader(test2Image);
    WriteBinaryFile("output/part2.tga", test2Image);

    //cout << "Part 2 Testing..... ";
    //compareImage(test2Image, part2Example);

    //Part 3
    Image pattern2 = ReadBinaryFile("input/pattern2.tga");
    Image tempImagePart3 = Multiply(layer1, pattern2);
    Image text = ReadBinaryFile("input/text.tga");
    //Image part3Example = ReadBinaryFile("src/test/EXAMPLE_part3.tga");
    Image part3 = Screen(tempImagePart3, text);
    WriteBinaryFile("output/part3.tga", part3);
    //cout << "Part 3 Testing..... ";
    //compareImage(part3Example, part3);

    //Part 4
    Image circles = ReadBinaryFile("input/circles.tga");
    Image tempPart4 = Multiply(circles, layer2);
    Image part4 = Subtract(tempPart4, pattern2);
    //Image part4Example = ReadBinaryFile("src/test/EXAMPLE_part4.tga");
    WriteBinaryFile("output/part4.tga", part4);
    //cout << "Part 4 Testing..... ";
    //compareImage(part4, part4Example);

    //Part 5
    Image part5 = Overlay(layer1, pattern1);
    //Image part5Example = ReadBinaryFile("src/test/EXAMPLE_part5.tga");
    WriteBinaryFile("output/part5.tga", part5);
    //cout << "Part 5 Testing..... ";
    //compareImage(part5, part5Example);

    //Part 6
    Image part6;
    copyHeader(part6, car);

    for(int i = 0; i < car.allPixels.size(); ++i)
    {
        Pixel tempPixel;
        int currentGreen = car.allPixels[i].green;
        currentGreen += 200;
        if (currentGreen > 255)
        {
            currentGreen = 255;
        }
        tempPixel.blue = car.allPixels[i].blue;
        tempPixel.red = car.allPixels[i].red;
        tempPixel.green = currentGreen;
        part6.allPixels.push_back(tempPixel);
    }

    //Image part6Example = ReadBinaryFile("src/test/EXAMPLE_part6.tga");
    WriteBinaryFile("output/part6.tga", part6);
    //cout << "Part 6 Testing..... ";
    //compareImage(part6, part6Example);

    //Part 7
    Image part7;
    copyHeader(part7, car);

    for(int i = 0; i < car.allPixels.size(); ++i)
    {
        Pixel tempPixel;
        tempPixel.blue = 0;
        tempPixel.green = car.allPixels[i].green;
        int red = car.allPixels[i].red;
        red *= 4;
        if (red > 255)
        {
            red = 255;
        }
        tempPixel.red = red;
        part7.allPixels.push_back(tempPixel);
    }
    //Image part7Example = ReadBinaryFile("src/test/EXAMPLE_part7.tga");
    WriteBinaryFile("output/part7.tga", part7);
    //cout << "Part 7 Testing..... ";
    //compareImage(part7, part7Example);

    //Part 8
    Image part8Red;
    Image part8Green;
    Image part8Blue;

    copyHeader(part8Red, car);
    copyHeader(part8Green, car);
    copyHeader(part8Blue, car);

    for(int i = 0; i < car.allPixels.size(); ++i) {
        Pixel tempPixel;

        tempPixel.red = car.allPixels[i].blue;
        tempPixel.green = car.allPixels[i].blue;
        tempPixel.blue = car.allPixels[i].blue;

        part8Blue.allPixels.push_back(tempPixel);
    }


    for(int i = 0; i < car.allPixels.size(); ++i) {
        Pixel tempPixel;

        tempPixel.red = car.allPixels[i].green;
        tempPixel.green = car.allPixels[i].green;
        tempPixel.blue = car.allPixels[i].green;

        part8Green.allPixels.push_back(tempPixel);

    }

    for(int i = 0; i < car.allPixels.size(); ++i) {
        Pixel tempPixel;

        tempPixel.red = car.allPixels[i].red;
        tempPixel.green = car.allPixels[i].red;
        tempPixel.blue = car.allPixels[i].red;

        part8Red.allPixels.push_back(tempPixel);
    }



    //Image part8ExRed = ReadBinaryFile("src/test/EXAMPLE_part8_r.tga");
    //Image part8ExGreen = ReadBinaryFile("src/test/EXAMPLE_part8_g.tga");
    //Image part8ExBlue = ReadBinaryFile("src/test/EXAMPLE_part8_b.tga");

    WriteBinaryFile("output/part8_g.tga", part8Green);
    WriteBinaryFile("output/part8_r.tga", part8Red);
    WriteBinaryFile("output/part8_b.tga", part8Blue);


    //cout << "Part 8 Red Testing..... ";
    //compareImage(part8Red, part8ExRed);
    //cout << "Part 8 Green Testing..... ";
    //compareImage(part8Green, part8ExGreen);
    //cout << "Part 8 Blue Testing..... ";
    //compareImage(part8Blue, part8ExBlue);

    //Part 9

    Image layerRed = ReadBinaryFile("input/layer_red.tga");
    Image layerGreen = ReadBinaryFile("input/layer_green.tga");
    Image layerBlue = ReadBinaryFile("input/layer_blue.tga");
    //Image part9Example = ReadBinaryFile("src/test/EXAMPLE_part9.tga");

    Image part9;

    copyHeader(part9, layerRed);

    for(int i = 0; i < layerRed.allPixels.size(); ++i)
    {
        Pixel tempPixel;
        tempPixel.red = layerRed.allPixels[i].red;
        tempPixel.blue = layerBlue.allPixels[i].blue;
        tempPixel.green = layerGreen.allPixels[i].green;
        part9.allPixels.push_back(tempPixel);
    }

    WriteBinaryFile("output/part9.tga", part9);	
    //cout << "Part 9 Testing..... ";
    //compareImage(part9, part9Example);

    //Part 10
    Image text2 = ReadBinaryFile("input/text2.tga");
    Image part10;
    copyHeader(part10, text2);
    //Image part10Example = ReadBinaryFile("src/test/EXAMPLE_part10.tga");
    for(int i = text2.allPixels.size() - 1; i >= 0; --i)
    {
        Pixel temp;
        temp.red = text2.allPixels[i].red;
        temp.green = text2.allPixels[i].green;
        temp.blue = text2.allPixels[i].blue;

        part10.allPixels.push_back(temp);
    }

    WriteBinaryFile("output/part10.tga", part10);
    //cout << "Part 10 Testing..... ";
    //compareImage(part10Example, part10);

    //Extra Credit
    Image exCredit = ExtraCredit(text, pattern1, car, circles);
    //Image exCreditCheck = ReadBinaryFile("test/EXAMPLE_extracredit.tga");
    WriteBinaryFile("output/extracredit.tga", exCredit);
    //Image myExCredit = ReadBinaryFile("output/extracredit.tga");
    //cout << "Extra Credit Testing..... ";
    //compareImage(myExCredit, exCreditCheck);

    return 0;
}
