#pragma once

#include <cmath>
#include <stdexcept>

struct Color {
    int r, g, b;

    Color(int r, int g, int b) {
        const int RED_THRESHOLD = 2;
        const int GREEN_LOWER_THRESHOLD = 2;
        const int GREEN_UPPER_THRESHOLD = 257;
        const int GREEN_MAX = 255;

        int redColor = r / RED_THRESHOLD;
        redColor = redColor > 1 ? redColor - 1 : 0;
        
        int greenColor = g * RED_THRESHOLD;
        greenColor = greenColor < GREEN_LOWER_THRESHOLD ? 0 : greenColor - GREEN_LOWER_THRESHOLD;
        greenColor = greenColor > GREEN_UPPER_THRESHOLD ? GREEN_MAX : greenColor;

        this->r = redColor;
        this->g = greenColor;
        this->b = b;
    }
};
