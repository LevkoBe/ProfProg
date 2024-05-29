#pragma once

#include <iostream>
#include <vector>
#include <Constants.hpp>

class Pizza {
    friend class PizzaBuilder;
    bool cheese;
    bool pepperoni;
    bool ham;
    bool sausage;
    bool mushrooms;
    bool onions;
    bool olives;
    bool pineapple;
    bool bacon;
    bool chicken;
    double cost;
public:
    Pizza() : cheese(false), pepperoni(false), ham(false), sausage(false), mushrooms(false), onions(false), olives(false), pineapple(false), bacon(false), chicken(false), cost(0.0) {}

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
};
