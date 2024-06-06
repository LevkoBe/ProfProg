#pragma once
#include <array>

constexpr double FILLING_VALUE = 42.0;
constexpr int ARRAY_SIZE = 1024;

class MegaData {
    std::array<float, ARRAY_SIZE> smallArray;
    std::array<double, ARRAY_SIZE * ARRAY_SIZE> bigArray;
public:
    MegaData() { reset(); }
    ~MegaData() = default;
    MegaData(const MegaData&) = delete;
    MegaData(MegaData&&) = delete;
    void reset() {
        smallArray.fill(FILLING_VALUE);
        bigArray.fill(FILLING_VALUE);
    }
};