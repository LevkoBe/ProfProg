#include <UnitTests.hpp>
#include <Triangle.hpp>
#include <Color.hpp>
#include <iostream>

int main() {
    UnitTests triangularUnitTests;

    triangularUnitTests.addTest("Expect_Area=6_When_Sides=3,4,5",
    [](){
        // Arrange
        Triangle triangle(3, 4, 5);

        // Act
        double area = triangle.calculateArea();

        // Assert
        ASSERT_EQ(area, 6.0);
    });

    triangularUnitTests.addTest("Expect_Area=1.5_When_Sides=1.5,2,2.5",
    [](){
        // Arrange
        Triangle triangle(1.5, 2, 2.5);

        // Act
        double area = triangle.calculateArea();

        // Assert
        ASSERT_EQ(area, 1.5);
    });

    triangularUnitTests.addTest("Expect_NotTriangle_When_NegativeSides",
    [](){
        // Arrange & Act
        bool isTriangle = Triangle::isTriangle(-1, 2, 3);

        // Assert
        ASSERT_EQ(isTriangle, false);
    });

    triangularUnitTests.addTest("Expect_IsTriangle_When_NormalSides",
    [](){
        // Arrange & Act
        bool isTriangle = Triangle::isTriangle(3, 4, 5);

        // Assert
        ASSERT_EQ(isTriangle, true);
    });

    triangularUnitTests.addTest("Expect_Exception_When_NegativeSides",
    [](){
        // Act and Assert
        ASSERT_THROW(Triangle triangle(-1, 2, 3), std::invalid_argument);
    });

    triangularUnitTests.addTest("Expect_Exception_When_SidesDoNotFormTriangle",
    [](){
        // Act and Assert
        ASSERT_THROW(Triangle triangle(1, 1, 3), std::invalid_argument);
    });

    // triangularUnitTests.run();

    UnitTests magicColorUnitTests;

    magicColorUnitTests.addTest("Expect_Green255_When_Green155",
    [](){
        // Arrange
        Color color(255, 155, 55);

        // Act
        int expectedRed = 255 / 2 - 1;
        int expectedGreen = 255;
        int expectedBlue = 55;

        // Assert
        ASSERT_EQ(color.r, expectedRed);
        ASSERT_EQ(color.g, expectedGreen);
        ASSERT_EQ(color.b, expectedBlue);
    });

    magicColorUnitTests.addTest("Expect_NormalResult_When_SimpleColors",
    [](){
        // Arrange
        Color color(55, 55, 55);

        // Act
        int expectedRed = 55 / 2 - 1;
        int expectedGreen = 55 * 2 - 2;
        int expectedBlue = 55;

        // Assert
        ASSERT_EQ(color.r, expectedRed);
        ASSERT_EQ(color.g, expectedGreen);
        ASSERT_EQ(color.b, expectedBlue);
    });

    magicColorUnitTests.addTest("Expect_000_When_000",
    [](){
        // Arrange
        Color color(0, 0, 0);

        // Act
        int expectedRed = 0;
        int expectedGreen = 0;
        int expectedBlue = 0;

        // Assert
        ASSERT_EQ(color.r, expectedRed);
        ASSERT_EQ(color.g, expectedGreen);
        ASSERT_EQ(color.b, expectedBlue);
    });

    magicColorUnitTests.run();
}
