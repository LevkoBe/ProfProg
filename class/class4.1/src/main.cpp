#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <print>
#include <UnitTests.hpp>
#include <PizzaBuilder.hpp>
#include <IngredientManager.hpp>

int main() {
    UnitTests pizzaTests;
    IngredientManager ingredientManager(FILENAME);

    pizzaTests.addTest("Pizza has cheese", []() {
        PizzaBuilder builder;
        builder.addIngredient(CHEESE);
        Pizza pizza = builder.build();
        return pizza.hasIngredient(CHEESE);
    });

    pizzaTests.addTest("Pizza has pepperoni", []() {
        PizzaBuilder builder;
        builder.addIngredient(PEPPERONI);
        Pizza pizza = builder.build();
        return pizza.hasIngredient(PEPPERONI);
    });

    pizzaTests.addTest("Pizza has ham", []() {
        PizzaBuilder builder;
        builder.addIngredient(HAM);
        Pizza pizza = builder.build();
        return pizza.hasIngredient(HAM);
    });
    
    pizzaTests.addTest("Pizza total cost", []() {
        PizzaBuilder builder;
        builder.addIngredient(CHEESE).addIngredient(HAM);
        Pizza pizza = builder.build();
        double cost = pizza.getCost();
        return cost == 3.5;
    });

    pizzaTests.addTest("Pizza ingredients are unique", []() {
        PizzaBuilder builder;
        builder.addIngredient(CHEESE).addIngredient(HAM).addIngredient(PEPPERONI);
        Pizza pizza = builder.build();
        std::vector<std::string> ingredients = pizza.getIngredients();
        std::sort(ingredients.begin(), ingredients.end());
        ingredients.erase(std::unique(ingredients.begin(), ingredients.end()), ingredients.end());
        return ingredients.size() == 3;
    });

    

    pizzaTests.run();

    std::vector<std::string> ingredientsAvailable = ingredientManager.readIngredients();

    PizzaBuilder builder;
    builder.superviseBuild(ingredientsAvailable);
    Pizza pizza = builder.build();

    std::cout << "Your pizza has the following ingredients: ";
    for (const auto& ingredient : pizza.getIngredients()) {
        std::cout << ingredient << " ";
        ingredientManager.deleteFirstOccurrence(ingredient);
    }
    std::cout << "\nTotal cost: $" << pizza.getCost() << std::endl;

    return 0;
};