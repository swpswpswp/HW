#pragma once
#include "Shape.h"
#include <corecrt_math.h>
#include <corecrt_math_defines.h>
class Pentagon : public Shape {
private:
    double side;
public:
    Pentagon(double s) : side(s) {}
    double getPerimeter() const override {
        return 5 * side;
    }
    double getArea() const override {
        return (5.0 / 4.0) * side * side / tan(M_PI / 5.0);
    }
};