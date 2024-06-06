#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <UnitTests.hpp>
#include <PizzaBuilder.hpp>
#include <IngredientManager.hpp>
#include "Constants.hpp"

std::vector<std::string> getKeys(const std::unordered_map<std::string, double>& map) {
    std::vector<std::string> keys;
    keys.reserve(map.size());
    for (const auto& pair : map) {
        keys.push_back(pair.first);
    }
    return keys;
}

int main() {
    UnitTests pizzaTests;

    pizzaTests.addTest("Pizza has cheese", []() {
        IngredientManager ingredientManager("ingredients.txt");
        std::unordered_map<std::string, double> ingredientsMap = ingredientManager.readIngredients();
        PizzaBuilder builder(ingredientsMap);

        builder.addIngredient(CHEESE);
        Pizza pizza = builder.build();

        ASSERT_EQ(pizza.hasIngredient(CHEESE), true);
    });

    pizzaTests.addTest("Pizza has pepperoni", []() {
        IngredientManager ingredientManager("ingredients.txt");
        std::unordered_map<std::string, double> ingredientsMap = ingredientManager.readIngredients();
        PizzaBuilder builder(ingredientsMap);

        builder.addIngredient(PEPPERONI);
        Pizza pizza = builder.build();

        ASSERT_EQ(pizza.hasIngredient(PEPPERONI), true);
    });

    pizzaTests.addTest("Pizza has ham", []() {
        IngredientManager ingredientManager("ingredients.txt");
        std::unordered_map<std::string, double> ingredientsMap = ingredientManager.readIngredients();
        PizzaBuilder builder(ingredientsMap);

        builder.addIngredient(HAM);
        Pizza pizza = builder.build();

        ASSERT_EQ(pizza.hasIngredient(HAM), true);
    });
    
    pizzaTests.addTest("Pizza total cost", []() {
        IngredientManager ingredientManager("ingredients.txt");
        std::unordered_map<std::string, double> ingredientsMap = ingredientManager.readIngredients();
        PizzaBuilder builder(ingredientsMap);

        builder.addIngredient(CHEESE).addIngredient(HAM);
        Pizza pizza = builder.build();
        double cost = pizza.getCost();

        ASSERT_EQ(cost, 3.5);
    });

    pizzaTests.addTest("Pizza ingredients are unique", []() {
        IngredientManager ingredientManager("ingredients.txt");
        std::unordered_map<std::string, double> ingredientsMap = ingredientManager.readIngredients();
        PizzaBuilder builder(ingredientsMap);

        builder.addIngredient(CHEESE).addIngredient(HAM).addIngredient(PEPPERONI);
        Pizza pizza = builder.build();
        std::vector<std::string> ingredients = pizza.getIngredients();
        std::sort(ingredients.begin(), ingredients.end());
        ingredients.erase(std::unique(ingredients.begin(), ingredients.end()), ingredients.end());

        ASSERT_EQ(ingredients.size(), 3);
    });

    pizzaTests.run();

    IngredientManager ingredientManager("ingredients.txt");
    std::unordered_map<std::string, double> ingredientsMap = ingredientManager.readIngredients();
    std::vector<std::string> ingredientsAvailable = getKeys(ingredientsMap);

    PizzaBuilder builder;
    builder.superviseBuild(ingredientsMap);
    Pizza pizza = builder.build();

    std::cout << "Your pizza has the following ingredients: ";
    for (const auto& ingredient : pizza.getIngredients()) {
        std::cout << ingredient << " ";
        ingredientManager.deleteFirstOccurrence(ingredient);
    }
    std::cout << "\nTotal cost: $" << pizza.getCost() << std::endl;

    return 0;
}
