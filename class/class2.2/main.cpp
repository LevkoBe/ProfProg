#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cstdlib>

bool validateFilename(const std::string& filename) {
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") {
        std::cout << "Filename must end with \".txt\"" << std::endl;
        return false;
    }
    return true;
}

bool validateColor(const std::string& color) {
    std::stringstream ss(color);
    int r, g, b;
    char comma1, comma2;
    if (!(ss >> r >> comma1 >> g >> comma2 >> b) || comma1 != ',' || comma2 != ',' ||
        r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        std::cout << "Invalid color format. Please enter in format \"R,G,B\" where R, G, and B are integers between 0 and 255." << std::endl;
        return false;
    }
    return true;
}

bool validateOutputFilename(const std::string& filename) {
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") {
        std::cout << "Output filename must end with \".txt\"" << std::endl;
        return false;
    }
    return true;
}

std::tuple<std::string, std::string, std::string> user_input() {
    std::string filename, color, o_filename;
    bool validInput = false;
    
    while (!validInput) {
        std::cout << "Please, enter the name of the file with the image: ";
        std::cin >> filename;
        if (validateFilename(filename)) {
            validInput = true;
        }
    }

    validInput = false;
    while (!validInput) {
        std::cout << "Please, enter your favorite color (format \"0,0,0\"): ";
        std::cin >> color;
        if (validateColor(color)) {
            validInput = true;
        }
    }

    validInput = false;
    while (!validInput) {
        std::cout << "Please, enter the output file name: ";
        std::cin >> o_filename;
        if (validateOutputFilename(o_filename)) {
            validInput = true;
        }
    }

    return std::make_tuple(filename, color, o_filename);
}

void fill_into_array(std::string array[16][16], int x, int y, const std::string& color, const std::string& fav_color) {
    array[x][y] = color;
    if (color == fav_color) {
        if (x > 0) {
            array[x - 1][y] = color;
        }
        if (y > 0) {
            array[x][y - 1] = color;
        }
    }
}

void display_array(const std::string array[16][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename, color, o_filename;
    std::tie(filename, color, o_filename) = user_input();

    std::string array[16][16];

    // read file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return 1;
    }
    int i = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        int j = 0;
        std::stringstream ss(line);
        std::string pixel;
        while (std::getline(ss, pixel, ' ')) {
            fill_into_array(array, i, j, pixel, color);
            j++;
        }
        i++;
    }
    inputFile.close();
    
    // write file
    std::ofstream outputFile(o_filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file " << o_filename << std::endl;
        return 1;
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            outputFile << array[i][j] << " ";
        }
        outputFile << std::endl;
    }
    outputFile.close();
    std::cout << "Image saved to " << o_filename << std::endl;

    return 0;
}
