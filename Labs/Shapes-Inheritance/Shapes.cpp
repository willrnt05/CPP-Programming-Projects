#include "Shapes.h"

//Shape
Shape::~Shape(){}

bool Shape2D::operator>( const Shape2D  &rhs) const
{
    return this->Area() > rhs.Area();
}

bool Shape2D::operator<(const Shape2D & rhs) const
{
    return this->Area() < rhs.Area();
}

bool Shape2D::operator==(const Shape2D &rhs) const
{
    return this->Area() == rhs.Area();
}

//2D Shape Declarations
void Shape2D::ShowArea() const
{
    cout << "The area of the " << getName2D() << " is : " << Area() << endl;
}


//3D Shape Declarations
void Shape3D::ShowVolume() const
{
    cout << "The volume of the " << getName3D() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const
{
    return this->Volume() > rhs.Volume();
}
bool Shape3D::operator<(const Shape3D & rhs) const
{
    return this->Volume() < rhs.Volume();
}
bool Shape3D::operator==(const Shape3D &rhs) const
{
    return this->Volume() == rhs.Volume();
}



//Square Declarations
float Square::Area() const
{
    return pow(sideLength, 2);
}

Square::Square(float s)
{
    sideLength = s;
}

string Square::getName2D() const {
    return "Square";
}

void Square::Scale(float scaleFactor)
{
    sideLength *= scaleFactor;
}

void Square::Display() const {
    cout << "The area of the Square is : " << Area() << endl;
    cout << "Length of a side: " << sideLength << endl;
}

//Triangle Declarations
float Triangle::Area() const
{
    return (baseLength * height * 0.5f);
}

Triangle::Triangle(float base, float height_)
{
    baseLength = base;
    height = height_;
}

string Triangle::getName2D() const {
    return "Triangle";
}

void Triangle::Scale(float scaleFactor)
{
    baseLength *= scaleFactor;
    height *= scaleFactor;
}

void Triangle::Display() const {
    cout << "The area of the Triangle is : " << Area() << endl;
    cout << "Base: " << baseLength << endl << "Height: " << height << endl;
}

//Circle Declarations
float Circle::Area() const
{
    return pi * pow(radius, 2);
}

Circle::Circle(float radius_)
{
    radius = radius_;
}

string Circle::getName2D() const
{
    return "Circle";
}

void Circle::Scale(float scaleFactor)
{
    radius *= scaleFactor;
}

void Circle::Display() const {
    cout << "The area of the Circle is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

//Triangular Pyramid Declarations
float TriangularPyramid::Volume() const
{
    //This formulas is wrong
    return ((1.0/3.0) * Triangle::Area() * heightPyramid);
}

TriangularPyramid::TriangularPyramid(float heightPyramid_, float base_, float height_)
        : Triangle(base_, height_) {

    this->height = height_;
    this->heightPyramid = heightPyramid_;
    this->base = base_;
}

string TriangularPyramid::getName3D() const {
    return "Triangular Pyramid";
}

void TriangularPyramid::Scale(float scaleFactor)
{
    height *= scaleFactor;
    base *= scaleFactor;
    heightPyramid *= scaleFactor;
}

void TriangularPyramid::Display() const {
    cout << "The volume of the TriangularPyramid is : " << Volume() << endl;
    cout << "The height is: " << heightPyramid << endl;
    cout << "The area of the Triangle is : " << Triangle::Area() << endl;
    cout << "Base: " << baseLength << endl;
    cout << "Height: " << height << endl;
}

//Cylinder Declarations
float Cylinder::Volume() const
{
    return pi * pow(radius, 2) * height;
}

Cylinder::Cylinder(float height_, float radius_)
{
    height = height_;
    radius = radius_;
}

string Cylinder::getName3D() const {
    return "Cylinder";
}

void Cylinder::Scale(float scaleFactor)
{
    height *= scaleFactor;
    radius *= scaleFactor;
}

void Cylinder::Display() const {
    cout << "The volume of the Cylinder is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    cout << "The area of the Circle is : " << pi * pow(radius, 2) << endl;
    cout << "Radius: " << radius << endl;
}

//Sphere Declarations
float Sphere::Volume() const
{
    return ((4.0/3.0) * pi * pow(radius, 3));
}

Sphere::Sphere(float radius_)
{
    radius = radius_;
}

string Sphere::getName3D() const {
    return "Sphere";
}

void Sphere::Scale(float scaleFactor)
{
    radius *= scaleFactor;
}

void Sphere::Display() const {
    cout << "The volume of the Sphere is : " << Volume() << endl;
    cout << "The area of the Circle is : " << pi * (pow(radius, 2)) << endl;
    cout << "Radius: " << radius << endl;
}