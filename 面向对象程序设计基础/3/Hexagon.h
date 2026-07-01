#pragma once
#include "Shape.h"
class Hexagon : public Shape {
private:
    double side;
public:
    Hexagon(double s) : side(s) {}
    double getPerimeter() const override {
        return 6 * side;
    }
    double getArea() const override {
        return (3 * sqrt(3) / 2) * side * side;
    }
};