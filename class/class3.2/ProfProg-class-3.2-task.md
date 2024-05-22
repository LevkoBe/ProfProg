**TASK. TDD**

***1. Use include/UnitTests.hpp as a testiing framework for this task.***
`clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 -Iinclude src/main.cpp src/Triangle.cpp -o test`

***2. Use TDD to implement the following task***

We should have a class that represents triangle defined by a triple - the length of all 3 sides. You should implement a method function of this class to calculate the area of the triangle.
Use TDD: Start you development with a failed test case: area of triangle with the sides 3,4,5 should equal to 6. Then you should make that test green and refactor test cases and other code. After all you should return back to the start and you should create a new failing test case. Try to fix the bug and so on.

***3. Another TDD task***
Let's represent color with RGB coordinates each in range 0,255. We need to have a member function that will be able to generate magic color with the following rules:
a) R component: divide by 2 and subtract 1 from it.
b) G component: corresponding component should be multiplied by 2 and subtract 2.
c) B component: blue component should be unchanged.
