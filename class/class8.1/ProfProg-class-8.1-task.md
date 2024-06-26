**TASK. Templates and concepts**

```clang++ -Wall -Wextra -Wpedantic -Werror -std=c++23 -Iinclude src/main.cpp -o test```

Use C++ templates and concepts to implement the following classes.
You should introduce a template class PricePresenter. This class should have a template parameter size_t PRIORITY.

Also it should have printTotalPrice method that takes 2 objects of maybe different types and priints the total price obtained with the formula PRIORITY * obj1.getCoefficient() * obj1.getBasePrice() + obj2.getCoefficient() * obj2.getBasePrice(). Ensure that template types for printTotalPrice are constrained properly with concept that guarantees presence of both getCoefficient and getBasePrice functions with return type double.

Create 3 classes(Milk, Cookies, Pineapple) that satisfy introduced concept. Write simple main function too check that PriicePresenter works fine with all that classes.

Fix the [clang problem](https://gist.github.com/krupkat/72a675bfb16244fe887ac77eb2b0fdfa).
