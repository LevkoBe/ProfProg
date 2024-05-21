#include <print>
#include <Helpers.hpp>
#include <UnitTests.hpp>

int main() {
    UnitTests testSuite;

    testSuite.addTest("Dummy_test1",
    [](){
        // Build:
        double value = 0.0;
    
        // Operate:
        auto result = dummyFunc(value);

        // Check:
        ASSERT_EQ(result, 0.0)
    });
    
    testSuite.addTest("Dummy_test2",
    [](){
        // Build:
        double value = 10.0;
    
        // Operate:
        auto result = dummyFunc(value);

        // Check:
        ASSERT_EQ(result, 10.0)
    });
    
    testSuite.addTest("Dummy_test3",
    [](){
        // Build:
        double value = -10.0;
    
        // Operate:
        auto result = dummyFunc(value);

        // Check:
        ASSERT_EQ(result, 0.0)
    });
    
    UnitTests stringTests;

    stringTests.addTest("Display \"string\" twice",
    [](){
        // Build:
        std::vector<int> numbers = {0, 1, 2};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "stringstring")
    });

    stringTests.addTest("Don't display \"string\" if numbers vector is empty",
    [](){
        // Build:
        std::vector<int> numbers = {};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "")
    });

    stringTests.addTest("Don't display \"string\" if numbers vector has no positive numbers",
    [](){
        // Build:
        std::vector<int> numbers = {-1, -2};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "")
    });

    stringTests.addTest("Don't display anything if string is empty",
    [](){
        // Build:
        std::vector<int> numbers = {0, 1, 2};
        std::string inputString = "";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "")
    });

    stringTests.addTest("Display \"string\" 6 times when biggest number is 6",
    [](){
        // Build:
        std::vector<int> numbers = {-13, -4, -151, 0, 1, 6, -123};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "stringstringstringstringstringstring")
    });

    // testSuite.run();
    stringTests.run();
}
