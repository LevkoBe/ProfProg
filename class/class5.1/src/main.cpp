#include "UnitTests.hpp"
#include "SinglePool.hpp"

std::shared_ptr<MegaData> help_acquire() {
    std::shared_ptr<SinglePool<MegaData>> pool = SinglePool<MegaData>::getInstance(5);
    return pool->acquire();
}

void help_release(std::shared_ptr<MegaData> data) {
    std::shared_ptr<SinglePool<MegaData>> pool = SinglePool<MegaData>::getInstance(5);
    pool->release(data);
}

size_t help_usedSize() {
    std::shared_ptr<SinglePool<MegaData>> pool = SinglePool<MegaData>::getInstance(5);
    return pool->usedSize();
}

void help_destroy() {
    std::shared_ptr<SinglePool<MegaData>> pool = SinglePool<MegaData>::getInstance(5);
    pool->destroy();
}

int main() {
    UnitTests megaDataTests;

    megaDataTests.addTest("expect_usedSize_when_acquiring", []() {
        // Arrange
        size_t expectedSize = 1;

        // Act
        for (int i = 0; i < 5; ++i) {
            help_acquire();

            // Assert
            ASSERT_EQ(help_usedSize(), expectedSize++);
        }
    });
    
    megaDataTests.addTest("expect_exception_when_exhausted", []() {
        // Arranged
        // Assert
        ASSERT_THROW(help_acquire(), std::runtime_error);
    });

    megaDataTests.addTest("expect_usedSize_when_releasing", []() {
        // Arrange
        help_destroy();
        std::vector<std::shared_ptr<MegaData>> acquired;
        for (int i = 0; i < 5; ++i) acquired.push_back(help_acquire());
        size_t expectedSize = 5;

        // Act
        for (auto& data : acquired) {
            help_release(data);

            // Assert
            ASSERT_EQ(help_usedSize(), --expectedSize);
        }
    });
    
    megaDataTests.addTest("expect_usedSize_when_acquired_again", []() {
        // Arrange
        std::vector<std::shared_ptr<MegaData>> acquired;
        for (int i = 0; i < 5; ++i) acquired.push_back(help_acquire());
        size_t expectedSize = 5;

        // Act
        for (auto& data : acquired) {
            help_release(data);
            help_acquire();

            // Assert
            ASSERT_EQ(help_usedSize(), expectedSize);
        }
    });

    megaDataTests.addTest("expect_usedSize_when_acquiring_concurrently", []() {
        // Arrange
        help_destroy();
        size_t expectedSize = 1;
        std::vector<std::thread> threads;
        constexpr int numThreads = 5;

        // Act
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([]() { help_acquire(); });
        }

        for (auto& t : threads) t.join();

        // Assert
        ASSERT_EQ(help_usedSize(), expectedSize * numThreads);
    });
    
    megaDataTests.addTest("expect_exception_when_exhausted_concurrently", []() {
        // Arrange
        help_destroy();
        std::vector<std::thread> threads;
        constexpr int numThreads = 5;

        auto malfunction = [&]() {
            for (int i = 0; i < numThreads; ++i)
                threads.emplace_back([]() {
                    for (int j = 0; j < 5; ++j) help_acquire();
                });

            for (auto& t : threads) t.join();
        };

        // Assert
        ASSERT_THROW(malfunction(), std::runtime_error);
    });

    megaDataTests.run();
    return 0;
}
