#pragma once
#include "Shape.h"
#include <corecrt_math.h>
class Triangle : public Shape {
private:
    double side;
public:
    Triangle(double s) : side(s) {}
    double getPerimeter() const override {
        return 3 * side;
    }
    double getArea() const override {
        return (sqrt(3) / 4) * side * side;
    }
};