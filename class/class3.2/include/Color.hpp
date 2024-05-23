#pragma once

#include <cmath>
#include <stdexcept>

struct Color {
    int r, g, b;

    Color(int r, int g, int b) {
        int redColor = r / 2;
        redColor = redColor > 1 ? redColor - 1 : 0;
        int greenColor = g * 2;
        greenColor = greenColor < 2 ? 0 : greenColor - 2;
        greenColor = greenColor > 257 ? 255 : greenColor;

        this->r = redColor;
        this->g = greenColor;
        this->b = b;
    }
};

