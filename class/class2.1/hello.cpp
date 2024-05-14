#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, int> userHistory;

void handleNameEntry(const string& name) {
    if (name == "bread") {
        userHistory.clear();
        cout << "Secret word was entered. Clearing all the history...";
            return;
    }
    if (userHistory.find(name) != userHistory.end()) {
        userHistory[name]++;
        cout << "Hello again(x" << userHistory[name] << "), " << name << "!";
    } else {
        userHistory[name] = 1;
        cout << "Welcome, " << name << "!";
    }
}

void handleNameDeletion(const string& name) {
    if (userHistory.find(name) != userHistory.end()) {
        userHistory.erase(name);
        cout << "History for " << name << " was deleted.";
    } else {
        cout << "No history found for " << name << ".";
    }
}

void errorMessage() {
    cout << "Please, enter a valid command (e.g. \"hello [username]\", or \"[username] delete\").";
}

void handleTwoParts(const string& input) {
    string firstPart = input.substr(0, input.find(' '));
    string secondPart = input.substr(input.find(' ') + 1);
    if (firstPart.empty() || secondPart.empty()) {
        errorMessage();
        return;
    }
    if (firstPart == "hello") {
        handleNameEntry(secondPart);
        return;
    }
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
        cout << "\n--> ";
        getline(cin, input);
        
        size_t spacePos = input.find(' ');
        if (spacePos == string::npos) {
            if (input.find("hello") == 0 || input.find("hi") == 0) {
                std::cout << "Hello!";
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
