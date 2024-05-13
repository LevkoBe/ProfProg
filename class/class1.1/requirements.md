```
**a.** As a cool programmer guy I want to have an ability to find the biggest negative value from the provided list of numbers. It will allow me to make my manual calculation faster.
**b.** As a cool mathematician I want to be able to get roots of the quadratic equation ax^2 + bx + c. It will allow me to avoid hard calculations related to determinant.
```

### Feature: Find the Biggest Negative Value

**Requirements**:

1. The system shall accept a list of numbers as input.
2. The system shall identify and return the largest negative value from the provided list.
3. The system shall handle cases where the list contains no negative values, returning an appropriate message.
4. The system shall provide the result promptly to optimize manual calculations.

### Feature: Quadratic Equation Solver

**Requirements**:

1. The system shall accept coefficients (a, b, and c) of a quadratic equation as input.
2. The system shall calculate the discriminant (b^2 - 4ac) to determine the nature of roots.
3. If the discriminant is negative, the system shall return a message indicating that the roots are complex.
4. If the discriminant is zero, the system shall calculate and return a single real root.
5. If the discriminant is positive, the system shall calculate and return two real roots.
6. The system shall provide accurate results with precision to hundredth.
7. The system shall handle cases where coefficients are zero or invalid input is provided.