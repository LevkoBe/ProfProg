#pragma once

#include <cmath>
#include <stdexcept>

class Triangle {
private:
    double a, b, c;

public:
    Triangle(double a, double b, double c);
    double calculateArea() const;
    static bool isTriangle(double a, double b, double c);
};

