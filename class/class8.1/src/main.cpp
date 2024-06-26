#include <iostream>
#include <concepts>
#include <print>

class Product {
public:
    virtual double getCoefficient() const = 0;
    virtual double getBasePrice() const = 0;
};

class Milk : public Product {
public:
    double getCoefficient() const override {
        return 1.0;
    }

    double getBasePrice() const override {
        return 2.0;
    }
};

class Cookies : public Product {
public:
    double getCoefficient() const override {
        return 2.0;
    }

    double getBasePrice() const override {
        return 5.0;
    }
};

class Pineapple : public Product {
public:
    double getCoefficient() const override {
        return 0.5;
    }

    double getBasePrice() const override {
        return 10.0;
    }
};

// Concept to check if a type has getCoefficient and getBasePrice methods
template<typename T>
concept HasPricingMethods = requires(T t) {
    { t.getCoefficient() } -> std::convertible_to<double>;
    { t.getBasePrice() } -> std::convertible_to<double>;
};

template <size_t PRIORITY>
class PricePresenter {
public:
    template <HasPricingMethods T1, HasPricingMethods T2>
    void printTotalPrice(const T1& obj1, const T2& obj2) const {
        double totalPrice = PRIORITY * obj1.getCoefficient() * obj1.getBasePrice() + obj2.getCoefficient() * obj2.getBasePrice();
        // std::cout << "Total price: " << totalPrice << std::endl;
        std::println("Total price: {}", totalPrice);
    }
};

int main() {
    Milk milk;
    Cookies cookies;
    Pineapple pineapple;

    PricePresenter<5> presenter;
    presenter.printTotalPrice(milk, cookies);
    presenter.printTotalPrice(milk, pineapple);
    presenter.printTotalPrice(cookies, pineapple);

    return 0;
}
