**TASK. Singleton behaviour for Object Pool**

Task 1. At this point we should have a class for object pool management(class-5.1). But now we want this pool to be accessible for all the program to request objects on demand. From the other hand declaration of global variables may cause a lot of problems - unintentional overwrite, memory allocation at program start even if no access was performed during program execution.
Therefore:
clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 -Iinclude src/main.cpp -o test
a) let's extend our class with singleton capabilities.
b) write 3 helper functions that will acquire and release objects from pool using singleton interface.
c) ensure that access to the pool is thread-safe e.g. few threads can acquire objects in parallel. 

