// PizzaBuilder.hpp
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <Pizza.hpp>
#include <Constants.hpp>

class PizzaBuilder {
    Pizza pizza;
    std::unordered_map<std::string, double> ingredientCosts;
public:
    PizzaBuilder() = default;

    PizzaBuilder(const std::unordered_map<std::string, double>& costs): ingredientCosts(costs) {}

    PizzaBuilder& setIngredientCosts(const std::unordered_map<std::string, double>& costs) {
        ingredientCosts = costs;
        return *this;
    }

    [[nodiscard("Do not drop pizza!")]]
    Pizza build() {
        return std::move(pizza);
    }

    PizzaBuilder& addIngredient(const std::string& ingredient) {
        auto it = ingredientCosts.find(ingredient);
        if (it != ingredientCosts.end()) {
            pizza.addIngredient(ingredient, it->second);
        }
        return *this;
    }

    void superviseBuild(const std::unordered_map<std::string, double>& ingredientsAvailable) {
        std::cout << "Available ingredients are: ";
        for (const auto& ingredient : ingredientsAvailable) {
            std::cout << ingredient.first << " ";
        }
        std::cout << "\nEnter the ingredients you want to add (type 'done' when finished): ";
        
        while (true) {
            std::string ingredient;
            std::cin >> ingredient;
            if (ingredient == "done") {
                break;
            }
            if (ingredientsAvailable.find(ingredient) != ingredientsAvailable.end()) {
                addIngredient(ingredient);
            } else {
                std::cout << "Invalid ingredient. Please enter a valid ingredient or 'done' to finish: ";
            }
        }
    }
};
