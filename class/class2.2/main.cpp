#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <print>

namespace {
    constexpr int kImageWidth = 16;
    constexpr int kImageHeight = 16;
    constexpr std::string_view kExpectedTxt = ".txt";

    struct Pixel {
        int r, g, b;

        Pixel() : r(0), g(0), b(0) {}
        Pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}

        bool isValid() const {
            return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
        }

        friend std::istream& operator>>(std::istream& is, Pixel& pixel) {
            char comma1, comma2;
            is >> pixel.r >> comma1 >> pixel.g >> comma2 >> pixel.b;
            if (comma1 != ',' || comma2 != ',') {
                is.setstate(std::ios_base::failbit);
            }
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel) {
            return os << pixel.r << ',' << pixel.g << ',' << pixel.b;
        }

        friend bool operator==(const Pixel& lhs, const Pixel& rhs) {
            return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
        }
    };

    class Image {
    private:
        Pixel pixels[kImageWidth][kImageHeight];
        Pixel fav_color;

    public:
        Image(Pixel& fav_color) : fav_color(fav_color) {}
        void setPixel(int x, int y, const Pixel& pixel) {
            pixels[x][y] = pixel;
            if (pixel == fav_color) {
                if (x > 0) { pixels[x - 1][y] = pixel; }
                if (y > 0) { pixels[x][y - 1] = pixel; }
            }
        }

        const Pixel& getPixel(int x, int y) const {
            return pixels[x][y];
        }

        bool saveToFile(const std::string& filename) const {
            std::ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                std::cerr << "Error opening file " << filename << std::endl;
                return false;
            }

            for (auto& row : pixels) {
                std::println(outputFile, "{}", row | std::views::join_with(" "));
            }
            outputFile.close();
            std::println("Image saved to {}", filename);
            return true;
        }
    };
}

bool validateFilename(const std::string& filename) {
    if (filename.length() < 4 || filename.find(kExpectedTxt) == std::string::npos) {
        std::println(stderr, "Filename must end with \".txt\"");
        return false;
    }
    return true;
}

bool validateColor(const Pixel& pixel) {
    if (!pixel.isValid()) {
        std::cerr << "Invalid color format. Please enter in format \"R,G,B\" where R, G, and B are integers between 0 and 255." << std::endl;
        return false;
    }
    return true;
}

Pixel user_input_color() {
    Pixel color;
    std::print("Please, enter your favorite color (format \"0,0,0\"): ");
    while (true) {
        if (!(std::cin >> color) || !validateColor(color)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::print("Please, enter your favorite color (format \"0,0,0\"): ");
        } else {
            break;
        }
    }
    return color;
}

int main() {
    std::string filename, o_filename;

    std::print("Please, enter the name of the file with the image: ");
    while (true) {
        std::cin >> filename;
        if (validateFilename(filename)) { break; }
        std::print("Please provide correct file name: ");
    }
    
    Pixel color = user_input_color();

    std::print("Please, enter the output file name: ");
    while (true) {
        std::cin >> o_filename;
        if (validateFilename(o_filename)) { break; }
        std::print("Please provide correct file name: ");
    }

    Image image(color);

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::println(stderr, "Error opening file {}", filename);
        return 1;
    }
    for (int i = 0; i < kImageHeight; ++i) {
        for (int j = 0; j < kImageWidth; ++j) {
            Pixel pixel;
            if (!(inputFile >> pixel)) {
                std::cerr << "Error reading pixel data from file." << std::endl;
                return 1;
            }
            image.setPixel(i, j, pixel);
        }
    }
    inputFile.close();

    if (!image.saveToFile(o_filename)) {
        return 1;
    }

    return 0;
}
