#pragma once
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

const float pi = 3.14159f;

//Destructor for Shape -- Empty -- Equal to zero and virtual.
class Shape {
public:
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;
    virtual ~Shape() = 0;
};


class Shape2D : virtual public Shape{
public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string getName2D() const = 0;
    bool operator>( const Shape2D  &rhs) const;
    bool operator<(const Shape2D & rhs) const;
    bool operator==(const Shape2D &rhs) const;

};

class Square : public Shape2D
{
public:
    float sideLength;

    void Scale(float scaleFactor);
    void Display() const;

    string getName2D() const;
    float Area() const;
    Square(float s = 0);
};

class Triangle : virtual public Shape2D
{
public:
    float baseLength;
    float height;

    void Scale(float scaleFactor);
    void Display() const;

    string getName2D() const;
    float Area() const;
    Triangle(float base = 0, float height_ = 0);
};

class Circle : public Shape2D
{
public:
    float radius;

    void Scale(float scaleFactor);
    void Display() const;

    string getName2D() const;
    float Area() const;

    Circle(float radius_ = 0);
};

class Shape3D : virtual public Shape{
public:
    virtual float Volume() const = 0;

    void ShowVolume() const;

    virtual string getName3D() const = 0;

    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D & rhs) const;
    bool operator==(const Shape3D &rhs) const;
};

class TriangularPyramid : public Shape3D, private Triangle
{
public:

    float height;
    float heightPyramid;
    float base;

    void Scale(float scaleFactor);
    void Display() const;

    string getName3D() const;
    float Volume() const;

    TriangularPyramid(float base = 0, float height = 0, float heightPyramid = 0);
};

class Cylinder : public Shape3D
{
public:
    float radius;
    float height;

    void Scale(float scaleFactor);
    void Display() const;

    string getName3D() const;
    float Volume() const;

    Cylinder(float height_ = 0, float radius_ = 0);
};

class Sphere : public Shape3D
{
public:
    float radius;

    void Scale(float scaleFactor);
    void Display() const;

    string getName3D() const;
    float Volume() const;

    Sphere(float radius_ = 0);
};






