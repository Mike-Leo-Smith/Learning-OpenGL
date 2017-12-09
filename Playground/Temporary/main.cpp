//#include <cmath>
//#include <iostream>
//
//class Shape
//{
//public:
//    virtual ~Shape() = default;
//    virtual double getArea() const = 0;
//    virtual double getPerim() const = 0;
//    int getVertexCount1() const;
//    int getVertexCount2() const;
//    virtual int getVertexCount3() const = 0;
//};
//
//class Circle : public Shape
//{
//private:
//    double _radius;
//
//public:
//    explicit Circle(double radius) : _radius(radius) {}
//    ~Circle() override = default;
//    double getArea() const override { return M_PI * _radius * _radius; }
//    double getPerim() const override { return 2 * M_PI * _radius; }
//    int getVertexCount3() const override { return 0; }
//};
//
//class Rectangle : public Shape
//{
//private:
//    double _width;
//    double _height;
//
//public:
//    Rectangle(double width, double height) : _width(width), _height(height) {}
//    ~Rectangle() override = default;
//    double getArea() const override { return _width * _height; }
//    double getPerim() const override { return 2 * (_width + _height); }
//    int getVertexCount3() const override { return 4; }
//};
//
//class Square : public Rectangle
//{
//public:
//    explicit Square(double width) : Rectangle(width, width) {}
//    ~Square() override = default;
//};
//
//int Shape::getVertexCount1() const
//{
//    if (dynamic_cast<const Rectangle *>(this)) {
//        return 4;
//    }
//    return 0;
//}
//
//int Shape::getVertexCount2() const
//{
//    if (typeid(*this) == typeid(Rectangle) || typeid(*this) == typeid(Square)) {
//        return 4;
//    }
//    return 0;
//}
//
//int main()
//{
//    Shape *shape = new Square(1.0);
//    std::cout << shape->getVertexCount1() << std::endl;
//    std::cout << shape->getVertexCount2() << std::endl;
//    return 0;
//}

#include <stdio.h>
#include <string.h>

int main()
{
    char arr[1001], arr1[1001];
    int a, b, c, d, t;
    gets(arr);
    c = strlen(arr);
    for (a = 0; a <= c; a++) {
        arr1[a] = arr[a] - '0';
    }
    for (a = 0; a <= t; a++) {
        d = 0;
        for (b = 0; b <= c; b++) {
            if (arr1[b] == a) {
                d++;
            }
        }
        if (d == 0) {
            continue;
        }
        printf("%d:%d\n", a, d);
    }
    return 0;
}