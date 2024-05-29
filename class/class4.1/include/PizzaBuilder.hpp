#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <Pizza.hpp>

class PizzaBuilder {
    std::unique_ptr<Pizza> pizzaPtr;
public:
    PizzaBuilder() : pizzaPtr(std::make_unique<Pizza>()) {}

    Pizza&& build() {
        return std::move(*pizzaPtr);
    }

    PizzaBuilder& addIngredient(const std::string& ingredient) {
        double ingredientCost = 0.0;
        if (ingredient == CHEESE) {
            pizzaPtr->cheese = true;
            ingredientCost = 1.5;
        } else if (ingredient == PEPPERONI) {
            pizzaPtr->pepperoni = true;
            ingredientCost = 2.0;
        } else if (ingredient == HAM) {
            pizzaPtr->ham = true;
            ingredientCost = 2.0;
        } else if (ingredient == SAUSAGE) {
            pizzaPtr->sausage = true;
            ingredientCost = 1.8;
        } else if (ingredient == MUSHROOMS) {
            pizzaPtr->mushrooms = true;
            ingredientCost = 1.2;
        } else if (ingredient == ONIONS) {
            pizzaPtr->onions = true;
            ingredientCost = 0.8;
        } else if (ingredient == OLIVES) {
            pizzaPtr->olives = true;
            ingredientCost = 1.0;
        } else if (ingredient == PINEAPPLE) {
            pizzaPtr->pineapple = true;
            ingredientCost = 1.5;
        } else if (ingredient == BACON) {
            pizzaPtr->bacon = true;
            ingredientCost = 2.2;
        } else if (ingredient == CHICKEN) {
            pizzaPtr->chicken = true;
            ingredientCost = 2.5;
        }
        pizzaPtr->cost += ingredientCost;
        return *this;
    }

    void superviseBuild(const std::vector<std::string>& ingredientsAvailable) {
        std::cout << "Available ingredients are: ";
        for (const auto& ingredient : ingredientsAvailable) {
            std::cout << ingredient << " ";
        }
        std::cout << "\nEnter the ingredients you want to add (type 'done' when finished): ";
        
        while (true) {
            std::string ingredient;
            std::cin >> ingredient;
            if (ingredient == "done") {
                break;
            }
            if (std::find(ingredientsAvailable.begin(), ingredientsAvailable.end(), ingredient) != ingredientsAvailable.end()) {
                addIngredient(ingredient);
            } else {
                std::cout << "Invalid ingredient. Please enter a valid ingredient or 'done' to finish: ";
            }
        }
    }
};
