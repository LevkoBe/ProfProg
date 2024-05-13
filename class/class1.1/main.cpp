#include <iostream>
#include <vector>
#include <sstream>

int solveQuadraticEquation() {
    std::string equation;
    std::cout << "Enter the equation (format: \"ax^2 + bx + c\"): ";
    std::getline(std::cin, equation);
    std::stringstream ss(equation);
    std::string part;
    int a, b, c;
    std::getline(ss, part, 'x');
    a = std::stoi(part);
    std::getline(ss, part, ' ');
    std::getline(ss, part, ' ');
    std::getline(ss, part, 'x');
    b = std::stoi(part);
    std::getline(ss, part, ' ');
    std::getline(ss, part, ' ');
    ss >> part;
    c = std::stoi(part);

    int discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        std::cout << "No real roots" << std::endl;
        return 0;
    }

    double root1 = (-b + std::sqrt(discriminant)) / (2 * a);
    double root2 = (-b - std::sqrt(discriminant)) / (2 * a);

    std::cout << "Roots are: " << root1 << " and " << root2 << std::endl;
    return 0;
}

int main() {
    std::cout << "Enter numbers separated by comma: ";
    std::string numbersString;
    std::vector<int> numbers;
    std::getline(std::cin, numbersString);

    std::stringstream ss(numbersString);
    std::string stringPart;
    while (std::getline(ss, stringPart, ',')) {
        numbers.push_back(std::stoi(stringPart));
    }

    int biggestNegative = -999999;
    for (int num : numbers) {
        if (num < 0 && num > biggestNegative) {
            biggestNegative = num;
        }
    }

    if (biggestNegative != -999999) {
        std::cout << "Biggest negative number is: " << biggestNegative << std::endl;
    } else {
        std::cout << "There are no negative numbers entered." << std::endl;
    }

    solveQuadraticEquation();

    return 0;
}
