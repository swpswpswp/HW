#pragma once
#include "Shape.h"
#include <corecrt_math_defines.h>
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }
    double getArea() const override {
        return M_PI * radius * radius;
    }
};