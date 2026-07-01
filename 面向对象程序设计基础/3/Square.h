#pragma once
#include "Shape.h"
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double getPerimeter() const override {
        return 4 * side;
    }
    double getArea() const override {
        return side * side;
    }
};