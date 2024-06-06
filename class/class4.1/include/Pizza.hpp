#pragma once

#include <iostream>
#include <vector>
#include <Constants.hpp>

class Pizza {
    friend class PizzaBuilder;
    bool cheese = false;
    bool pepperoni = false;
    bool ham = false;
    bool sausage = false;
    bool mushrooms = false;
    bool onions = false;
    bool olives = false;
    bool pineapple = false;
    bool bacon = false;
    bool chicken = false;
    double cost = 0.0;
public:
    std::vector<std::string> getIngredients() const {
        std::vector<std::string> ingredients;

        if (cheese) ingredients.push_back(CHEESE);
        if (pepperoni) ingredients.push_back(PEPPERONI);
        if (ham) ingredients.push_back(HAM);
        if (sausage) ingredients.push_back(SAUSAGE);
        if (mushrooms) ingredients.push_back(MUSHROOMS);
        if (onions) ingredients.push_back(ONIONS);
        if (olives) ingredients.push_back(OLIVES);
        if (pineapple) ingredients.push_back(PINEAPPLE);
        if (bacon) ingredients.push_back(BACON);
        if (chicken) ingredients.push_back(CHICKEN);

        return ingredients;
    }

    bool hasIngredient(const std::string& ingredient) const {
        return (ingredient == CHEESE && cheese) || 
               (ingredient == PEPPERONI && pepperoni) || 
               (ingredient == HAM && ham) || 
               (ingredient == SAUSAGE && sausage) || 
               (ingredient == MUSHROOMS && mushrooms) || 
               (ingredient == ONIONS && onions) || 
               (ingredient == OLIVES && olives) || 
               (ingredient == PINEAPPLE && pineapple) || 
               (ingredient == BACON && bacon) || 
               (ingredient == CHICKEN && chicken);
    }

    double getCost() const {
        return cost;
    }
    
    void addIngredient(const std::string& ingredient, double ingredientCost) {
        if (ingredient == CHEESE && !cheese) {
            cheese = true;
            cost += ingredientCost;
        }
        else if (ingredient == PEPPERONI && !pepperoni) {
            pepperoni = true;
            cost += ingredientCost;
        }
        else if (ingredient == HAM && !ham) {
            ham = true;
            cost += ingredientCost;
        }
        else if (ingredient == SAUSAGE && !sausage) {
            sausage = true;
            cost += ingredientCost;
        }
        else if (ingredient == MUSHROOMS && !mushrooms) {
            mushrooms = true;
            cost += ingredientCost;
        }
        else if (ingredient == ONIONS && !onions) {
            onions = true;
            cost += ingredientCost;
        }
        else if (ingredient == OLIVES && !olives) {
            olives = true;
            cost += ingredientCost;
        }
        else if (ingredient == PINEAPPLE && !pineapple) {
            pineapple = true;
            cost += ingredientCost;
        }
        else if (ingredient == BACON && !bacon) {
            bacon = true;
            cost += ingredientCost;
        }
        else if (ingredient == CHICKEN && !chicken) {
            chicken = true;
            cost += ingredientCost;
        }
        else {
            throw std::runtime_error("Invalid ingredient");
        }
    }
};
