#include "Helpers.hpp"

double dummyFunc(double x) {
    return x > 0 ? x : 0;
}

std::string repeatString(std::vector<int>& numbers, std::string& stringToRepeat) {
    int biggestPositive = 0;
    for (auto& number : numbers) {
        if (number > biggestPositive) {
            biggestPositive = number;
        }
    }
    std::string finalString = "";
    for (int i = 0; i < biggestPositive; i++) {
        finalString += stringToRepeat;
    }
    return finalString;
}
