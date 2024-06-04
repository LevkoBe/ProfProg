#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

class IngredientManager {
    std::string filename;

public:
    IngredientManager(const std::string& file) : filename(file) {}

    std::unordered_map<std::string, double> readIngredients() {
        std::unordered_map<std::string, double> ingredients;
        std::string line;
        std::ifstream file(filename);
        if (file.is_open()) {
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string ingredient;
                double cost;
                if (iss >> ingredient >> cost) {
                    ingredients[ingredient] = cost;
                }
            }
            file.close();
        } else {
            std::cerr << "Unable to open file." << std::endl;
        }
        return ingredients;
    }

    void writeIngredients(const std::unordered_map<std::string, double>& ingredients) {
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& pair : ingredients) {
                outputFile << pair.first << " " << pair.second << std::endl;
            }
            outputFile.close();
        }
    }

    void deleteFirstOccurrence(const std::string& ingredient) {
        auto ingredients = readIngredients();
        auto it = ingredients.find(ingredient);
        if (it != ingredients.end()) {
            ingredients.erase(it);
            writeIngredients(ingredients);
        }
    }
};
