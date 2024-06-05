#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include "UnitTests.hpp"

constexpr double FILLING_VALUE = 42.0;
constexpr int ARRAY_SIZE = 1024;

class MegaData {
    std::array<float, ARRAY_SIZE> smallArray;
    std::array<double, ARRAY_SIZE * ARRAY_SIZE> bigArray;
public:
    MegaData() {
        reset();
    }
    void reset() {
        smallArray.fill(FILLING_VALUE);
        bigArray.fill(FILLING_VALUE);
    }
};

class MegaDataPool {
    std::vector<std::unique_ptr<MegaData>> megaDataVector;
    std::vector<bool> megaDataVectorUsed;
public:
    MegaDataPool(int size) : megaDataVector(size), megaDataVectorUsed(size, false) {
        for (auto& ptr : megaDataVector) {
            ptr = std::make_unique<MegaData>();
        }
    }
    MegaData& acquire() {
        for (size_t i = 0; i < megaDataVector.size(); ++i) {
            if (!megaDataVectorUsed[i]) {
                megaDataVectorUsed[i] = true;
                return *megaDataVector[i];
            }
        }
        throw std::runtime_error("Pool exhausted");
    }
    void release(MegaData& MDReference) {
        for (size_t i = 0; i < megaDataVector.size(); ++i) {
            if (&MDReference == megaDataVector[i].get()) {
                megaDataVectorUsed[i] = false;
                return;
            }
        }
        throw std::invalid_argument("Invalid MegaData object");
    }
    size_t size() const {
        return megaDataVector.size();
    }
    size_t usedSize() const {
        size_t count = 0;
        for (bool used : megaDataVectorUsed) {
            if (used) count++;
        }
        return count;
    }
};

int main() {
    UnitTests megaDataTests;

    megaDataTests.addTest("expect_usedSize_when_acquiring", []() {
        // Arrange
        MegaDataPool pool(5);
        size_t expectedSize = 1;

        // Act
        for (int i = 0; i < 5; ++i) {
            pool.acquire();

            // Assert
            ASSERT_EQ(pool.usedSize(), expectedSize++);
        }
    });
    
    megaDataTests.addTest("expect_exception_when_exhausted", []() {
        // Arrange
        MegaDataPool pool(5);
        for (int i = 0; i < 5; ++i) {
            pool.acquire();
        }

        // Assert
        ASSERT_THROW(pool.acquire(), std::runtime_error);
    });

    megaDataTests.addTest("expect_usedSize_when_releasing", []() {
        // Arrange
        MegaDataPool pool(5);
        std::vector<MegaData*> acquired;
        for (int i = 0; i < 5; ++i) {
            acquired.push_back(&pool.acquire());
        }
        size_t expectedSize = 5;

        // Act
        for (auto* data : acquired) {
            pool.release(*data);

            // Assert
            ASSERT_EQ(pool.usedSize(), --expectedSize);
        }
    });
    
    megaDataTests.addTest("expect_usedSize_when_acquired_again", []() {
        // Arrange
        MegaDataPool pool(5);
        std::vector<MegaData*> acquired;
        for (int i = 0; i < 5; ++i) {
            acquired.push_back(&pool.acquire());
        }
        size_t expectedSize = 5;

        // Act
        for (auto* data : acquired) {
            pool.release(*data);
            pool.acquire();

            // Assert
            ASSERT_EQ(pool.usedSize(), expectedSize);
        }
    });

    megaDataTests.run();
    return 0;
}
