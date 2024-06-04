#include "Helpers.hpp"

double dummyFunc(double x) {
    return x > 0 ? x : 0;
}

std::string repeatString(const std::vector<int>& numbers, const std::string& stringToRepeat) {
    auto biggestPositive = numbers.empty() ? 0 : std::ranges::max(numbers);
    std::string finalString = "";
    for (int i = 0; i < biggestPositive; i++) {
        finalString += stringToRepeat;
    }
    return finalString;
}
