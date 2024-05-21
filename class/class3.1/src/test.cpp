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

    stringTests.addTest("Expect_stringstring_When_2IsBiggestNumber",
    [](){
        // Build:
        std::vector<int> numbers = {0, 1, 2};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "stringstring")
    });

    stringTests.addTest("Expect_EmptyString_When_NoNumbers",
    [](){
        // Build:
        std::vector<int> numbers = {};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "")
    });

    stringTests.addTest("Expect_EmptyString_When_NoPositiveNumbers",
    [](){
        // Build:
        std::vector<int> numbers = {-1, -2};
        std::string inputString = "string";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "")
    });

    stringTests.addTest("Expect_EmptyString_When_EmptyString",
    [](){
        // Build:
        std::vector<int> numbers = {0, 1, 2};
        std::string inputString = "";
    
        // Operate:
        auto result = repeatString(numbers, inputString);

        // Check:
        ASSERT_EQ(result, "")
    });

    stringTests.addTest("Expect_string6times_When_6IsBiggestNumber",
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
