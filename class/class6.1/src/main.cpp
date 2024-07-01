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
#include <queue>
#include <condition_variable>
#include <format>

struct Message {
    virtual std::string getMessage() const = 0;
    virtual std::string getType() const = 0;
    virtual ~Message() = default;
};

struct GreenMessage : Message {
    std::string message;
    int counter;

    GreenMessage(std::string message, int counter) : message(message), counter(counter) {}

    std::string getMessage() const override {
        return std::format("{} {}", message, counter);
    }

    std::string getType() const override {
        return "GreenMessage";
    }

    ~GreenMessage() override = default;
};

struct BlueMessage : Message {
    double value1;
    double value2;

    BlueMessage(double value1, double value2) : value1(value1), value2(value2) {}

    std::string getMessage() const override {
        return std::format("{} {}", value1, value2);
    }

    std::string getType() const override {
        return "BlueMessage";
    }

    ~BlueMessage() override = default;
};

struct OrangeMessage : Message {
    std::string string1;
    std::string string2;
    int integer;
    double doubleValue;

    OrangeMessage(std::string string1, std::string string2, int integer, double doubleValue)
        : string1(string1), string2(string2), integer(integer), doubleValue(doubleValue) {}

    std::string getMessage() const override {
        return std::format("{} {} {} {}", string1, string2, integer, doubleValue);
    }

    std::string getType() const override {
        return "OrangeMessage";
    }

    ~OrangeMessage() override = default;
};

class MessageDispatcher {
private:
    std::map<std::string, std::vector<std::function<void(std::shared_ptr<Message>)>>> subscribers;
    std::mutex mtx;
    std::queue<std::shared_ptr<Message>> messageQueue;
    std::condition_variable cv;
    bool stop = false;

public:
    MessageDispatcher() {
        std::thread(&MessageDispatcher::dispatchMessages, this).detach();
    }

    void subscribe(const std::string& messageType, std::function<void(std::shared_ptr<Message>)> callback) {
        std::lock_guard<std::mutex> lock(mtx);
        subscribers[messageType].push_back(callback);
    }

    void publish(std::shared_ptr<Message> message) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            messageQueue.push(message);
        }
        cv.notify_one();
    }

    void dispatchMessages() {
        while (true) {
            std::shared_ptr<Message> message;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] { return !messageQueue.empty() || stop; });
                if (stop && messageQueue.empty()) return;
                message = messageQueue.front();
                messageQueue.pop();
            }
            std::string messageType = message->getType();
            if (subscribers.find(messageType) != subscribers.end()) {
                for (auto& callback : subscribers[messageType]) {
                    callback(message);
                }
            }
        }
    }

    void stopDispatcher() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
    }

    ~MessageDispatcher() {
        stopDispatcher();
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
