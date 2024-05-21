#include <iostream>
#include <string>
#include <unordered_map>
#include <print>

using namespace std;

namespace {
    constexpr auto commandHello = "hello";
    constexpr auto commandDelete = "delete";
    constexpr auto commandSecretPhrase = "bread";
}

class NameCounter {
    unordered_map<string, uint32_t> userHistory;
public:
    void incrementCounter(const std::string& name) {
        userHistory[name]++;
    }

    void greet(const std::string& name) {
        if (userHistory[name] == 1) {
            std::println("Welcome, {}!", name);
        } else {
            std::println("Hello again(x{}), {}!", userHistory[name], name);
        }
    }

    void deleteCounter(const std::string& name) {
        if (userHistory.find(name) != userHistory.end()) {
            userHistory.erase(name);
            std::println("History for {} was deleted.", name);
        } else {
            std::println("No history found for {}.", name);
        }
    }

    void clearAll() {
        userHistory.clear();
    }
};

void handleNameEntry(NameCounter& userHistory, const string& name) {
    if (name == commandSecretPhrase) {
        std::println("Secret word was entered. Clearing all the history...");
        userHistory.clearAll();
    } else {
        userHistory.incrementCounter(name);
        userHistory.greet(name);
    }
}

void errorMessage() {
    std::println("Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").");
}

void handleTwoParts(NameCounter& userHistory, const string& input) {
    size_t spacePos = input.find(' ');
    if (spacePos == string::npos) {
        errorMessage();
        return;
    }
    
    string firstPart = input.substr(0, spacePos);
    string secondPart = input.substr(spacePos + 1);

    if (firstPart.empty() || secondPart.empty()) {
        errorMessage();
        return;
    }

    if (firstPart == commandHello) {
        handleNameEntry(userHistory, secondPart);
    } else if (secondPart == commandDelete) {
        userHistory.deleteCounter(firstPart);
    } else {
        errorMessage();
    }
}

int main() {
    NameCounter userHistory;
    string input;
    
    while (true) {
        std::print("--> ");
        std::getline(cin, input);

        if (input == "exit") {
            break;
        }

        size_t spacePos = input.find(' ');
        if (spacePos == string::npos) {
            if (input.find(commandHello) == 0 || input.find("hi") == 0) {
                std::println("Hello!");
            } else {
                errorMessage();
            }
        } else {
            handleTwoParts(userHistory, input);
        }
    }

    return 0;
}
