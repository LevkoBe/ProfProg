#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class IngredientManager {
    std::string filename;

public:
    IngredientManager(const std::string& file) : filename(file) {}

    std::vector<std::string> readIngredients() {
        std::vector<std::string> ingredients;
        std::string line;
        std::ifstream file(filename);
        if (file.is_open()) {
            while (std::getline(file, line)) {
                ingredients.push_back(line);
            }
            file.close();
        } else {
            std::cerr << "Unable to open file." << std::endl;
        }
        return ingredients;
    }

    void writeIngredients(const std::vector<std::string>& ingredients) {
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& ingredient : ingredients) {
                outputFile << ingredient << std::endl;
            }
            outputFile.close();
        }
    }

    void deleteFirstOccurrence(const std::string& ingredient) {
        std::vector<std::string> ingredients = readIngredients();
        auto it = std::find(ingredients.begin(), ingredients.end(), ingredient);
        if (it != ingredients.end()) {
            ingredients.erase(it);
            writeIngredients(ingredients);
        }
    }
};
