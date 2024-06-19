#include <iostream>
#include <print>
#include <vector>
#include <ostream>
#include <UnitTests.hpp>

struct Rectangle {
    double width = 0.0;
    double height = 0.0;
    double area = 0.0;

    void calculateArea() {
        area = width * height;
    }

    bool canBePlacedInside(const Rectangle& other) const {
        return width <= other.width && height <= other.height;
    }

    double biggerSide() const {
        return height > width ? height : width;
    }

    std::string toString() const {
        return std::format("[Rect: (Width: {}, Height: {}, Area: {})]", width, height, area);
    }

    friend std::istream& operator>>(std::istream& is, Rectangle& rect) {
        is >> rect.width >> rect.height;
        rect.calculateArea();
        return is;
    }
};

void normalFlow() {
    std::vector<Rectangle> rectangles(5);
    double biggestArea = 0;
    double smallestArea = std::numeric_limits<double>::max();
    constexpr int RECTANGLES_COUNT = 5;

    for (int i = 0; i < RECTANGLES_COUNT; i++) {
        std::println("Enter rectangle {}: ", i + 1);
        std::cin >> rectangles[i];
        biggestArea = std::max(biggestArea, rectangles[i].area);
        smallestArea = std::min(smallestArea, rectangles[i].area);
    }
    
    for (int i = 0; i < RECTANGLES_COUNT; i++)
        for (int j = 0; j < RECTANGLES_COUNT; j++)
            if (rectangles[i].canBePlacedInside(rectangles[j]) && i != j)
                std::println("Rectangle {} can be placed inside Rectangle {}", i + 1, j + 1);

    std::println("The biggest area: {}", biggestArea);
    std::println("Number of rectangles: {}", RECTANGLES_COUNT);
    std::println("The smallest area: {}", smallestArea);

    for (const auto& rect : rectangles)
        std::println("The bigger side of rectangle {} is {}", rect.toString(), rect.biggerSide());
}

int main() {
    // normalFlow();
    UnitTests tests;

    tests.addTest("area_from_rectangle", []() {
        Rectangle rect{3.0, 4.0};
        rect.calculateArea();
        ASSERT_EQ(rect.area, 12.0);
    });
    tests.addTest("area_from_abnormalRectangle", []() {
        Rectangle rect{3.0, -4.0};
        rect.calculateArea();
        ASSERT_EQ(rect.area, -12.0);
    });
    tests.addTest("trueFalse_when_placingRectangleInsideAnother", []() {
        Rectangle rect1{2.0, 3.0};
        Rectangle rect2{1.0, 1.0};
        ASSERT_EQ(rect1.canBePlacedInside(rect2), false);
        ASSERT_EQ(rect2.canBePlacedInside(rect1), true);
    });
    tests.addTest("bigger_side", []() {
        Rectangle rect{3.0, 4.0};
        ASSERT_EQ(rect.biggerSide(), 4.0);
    });

    tests.run();
    return 0;
}
