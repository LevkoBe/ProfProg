#include <Triangle.hpp>
#include <stdexcept>

Triangle::Triangle(double a, double b, double c) {
    if (!isTriangle(a, b, c)) {
        throw std::invalid_argument("Invalid triangle sides");
    }
    this->a = a;
    this->b = b;
    this->c = c;
}

double Triangle::calculateArea() const {
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

bool Triangle::isTriangle(double a, double b, double c) {
    return a > 0 && b > 0 && c > 0 &&
           a + b > c && a + c > b && b + c > a;
}
