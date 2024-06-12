#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <random>
#include <vector>
#include <map>
#include <memory>
#include <print>

struct Message {
    virtual std::string getMessage() const = 0;
    virtual std::string getType() const = 0;
    virtual ~Message() = default; // Add virtual destructor
};

struct GreenMessage : Message {
    std::string message;
    int counter;

    GreenMessage(std::string message, int counter) : message(message), counter(counter) {}

    std::string getMessage() const override {
        return message + " " + std::to_string(counter);
    }

    std::string getType() const override {
        return "GreenMessage";
    }

    ~GreenMessage() override = default; // Virtual destructor
};

struct BlueMessage : Message {
    double value1;
    double value2;

    BlueMessage(double value1, double value2) : value1(value1), value2(value2) {}

    std::string getMessage() const override {
        return std::to_string(value1) + " " + std::to_string(value2);
    }

    std::string getType() const override {
        return "BlueMessage";
    }

    ~BlueMessage() override = default; // Virtual destructor
};

struct OrangeMessage : Message {
    std::string string1;
    std::string string2;
    int integer;
    double doubleValue;

    OrangeMessage(std::string string1, std::string string2, int integer, double doubleValue) 
        : string1(string1), string2(string2), integer(integer), doubleValue(doubleValue) {}

    std::string getMessage() const override {
        return string1 + " " + string2 + " " + std::to_string(integer) + " " + std::to_string(doubleValue);
    }

    std::string getType() const override {
        return "OrangeMessage";
    }

    ~OrangeMessage() override = default; // Virtual destructor
};

class MessageDispatcher {
private:
    std::map<std::string, std::vector<std::function<void(std::shared_ptr<Message>)>>> subscribers;
    std::mutex mtx;

public:
    void subscribe(const std::string& messageType, std::function<void(std::shared_ptr<Message>)> callback) {
        std::lock_guard<std::mutex> lock(mtx);
        subscribers[messageType].push_back(callback);
    }

    void publish(std::shared_ptr<Message> message) {
        std::lock_guard<std::mutex> lock(mtx);
        std::string messageType = message->getType();
        if (subscribers.find(messageType) != subscribers.end()) {
            for (auto& callback : subscribers[messageType]) {
                callback(message);
            }
        }
    }
};

void generateMessages(MessageDispatcher& dispatcher) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);

    while (true) {
        int messageType = dis(gen);
        switch (messageType) {
            case 1: {
                dispatcher.publish(std::make_shared<GreenMessage>("Green", dis(gen)));
                break;
            }
            case 2: {
                dispatcher.publish(std::make_shared<BlueMessage>(dis(gen) * 1.1, dis(gen) * 2.2));
                break;
            }
            case 3: {
                dispatcher.publish(std::make_shared<OrangeMessage>("Orange1", "Orange2", dis(gen), dis(gen) * 3.3));
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    MessageDispatcher dispatcher;

    dispatcher.subscribe("GreenMessage", [](std::shared_ptr<Message> message) {
        std::println("Received GreenMessage: {}", message->getMessage());
    });

    dispatcher.subscribe("BlueMessage", [](std::shared_ptr<Message> message) {
        std::println("Received BlueMessage: {}", message->getMessage());
    });

    // dispatcher.subscribe("OrangeMessage", [](std::shared_ptr<Message> message) {
    //     std::println("Received OrangeMessage: {}", message->getMessage());
    // });

    std::thread t1(generateMessages, std::ref(dispatcher));
    std::thread t2(generateMessages, std::ref(dispatcher));

    t1.join();
    t2.join();

    return 0;
}
