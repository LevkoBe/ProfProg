#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// It is better to encapsulate it to some class
// and have member method to do different operations on the data
// Other code may rely on the proposed API but internals will be hidden which will give more flexible way to support the code.
// Prefer to use int32_t or uint32_t instead of int to specify the exact size and limits
unordered_map<string, int> userHistory;

void handleNameEntry(const string& name) {
    if (name == "bread") {
        userHistory.clear();
        // Let's try std::println here and in other places
        cout << "Secret word was entered. Clearing all the history..." << endl;
        // bad indent for return below:
            return;
    }

    // If you will use encapsulation then you will able to add some method like
    // int incrementUsage(const std::string& name)
    // which will return the new count value
    //  auto count = userHistory.incrementUsage(name);
    //  if (count == 1) {
    //      std::println("Welcome, {}!", name);
    //  } else {
    //      std::println("Hello again(x{}), {}!", count, name);
    //  }

    if (userHistory.find(name) != userHistory.end()) {
        userHistory[name]++;
        // std::println("Hello again(x{}), {}!", userHistory[name], name);
        cout << "Hello again(x" << userHistory[name] << "), " << name << "!" << endl;
    } else {
        userHistory[name] = 1;
        // std::println("Welcome, {}!", name);
        cout << "Welcome, " << name << "!" << endl;
    }
}

void handleNameDeletion(const string& name) {
    if (userHistory.find(name) != userHistory.end()) {
        userHistory.erase(name);
        cout << "History for " << name << " was deleted." << endl;
    } else {
        cout << "No history found for " << name << "." << endl;
    }
}

void errorMessage() {
    cout << "Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\")." << endl;
}

void handleTwoParts(const string& input) {
    string firstPart = input.substr(0, input.find(' '));
    string secondPart = input.substr(input.find(' ') + 1);
    if (firstPart.empty() || secondPart.empty()) {
        errorMessage();
        return;
    }

    // Avoid hardcoded values like "hello" and "delete"
    // It is better to use constants for example
    // namespace {
    //     constexpr auto commanHello = "hello";
    //     constexpr auto commandDelete = "delete";
    //     constexpr auto commandSecretErase = "bread";
    // }
    // It allows to adjust things faster or localize program to another language faster if needed.
    if (firstPart == "hello") {
        handleNameEntry(secondPart);
        return;
    }
    // Minor: In some cases if we return  from if parts then we can linearize the code like:
    // if (firstPart == "hello") {
    //     handleNameEntry(secondPart);
    //     return;
    // }
    // if (firstPart == "delete") {
    //     handleNameDeletion(secondPart);
    //     return;
    // }
    // But it is not always the case - you can decide based on your own perception on how readable it is.
    else if (secondPart == "delete") {
        handleNameDeletion(firstPart);
        return;
    }
    else {
        errorMessage();
        return;
    }
}

int main() {
    string input;
    
    while (true) {
        cout << "--> ";
        getline(cin, input);
        
        size_t spacePos = input.find(' ');
        if (spacePos == string::npos) {
            // We have copy paste of hello here thats why we need constants - any copy paste causes potential issues during code support
            if (input.find("hello") == 0 || input.find("hi") == 0) {
                std::cout << "Hello!" << endl;
                continue;
            }
            if (input == "exit") {
                break;
            }
            else {
                errorMessage();
            }
            continue;
        }

        handleTwoParts(input);
    }

    return 0;
}
