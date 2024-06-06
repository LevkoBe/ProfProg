#pragma once
#include <memory>
#include <vector>
#include <mutex>
#include <stdexcept>
#include "MegaData.hpp"

constexpr int DEFAULT_POOL_SIZE = 5;

template <typename T>
class SinglePool {
private:
    static std::shared_ptr<SinglePool<T>> singlePool;
    static std::mutex mtx;

    std::vector<std::shared_ptr<T>> mdVector;
    std::vector<bool> mdVectorUsed;

protected:
    SinglePool(int size) : mdVector(size), mdVectorUsed(size, false) {
        for (auto& ptr : mdVector) {
            ptr = std::make_shared<T>();
        }
    }

public:
    static std::shared_ptr<SinglePool<T>> getInstance(int size = DEFAULT_POOL_SIZE) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!singlePool) {
            singlePool = std::shared_ptr<SinglePool<T>>(new SinglePool<T>(size));
        }
        return singlePool;
    }

    SinglePool(const SinglePool&) = delete;
    void operator=(const SinglePool&) = delete;

    std::shared_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(mtx);
        for (size_t i = 0; i < mdVector.size(); ++i) {
            if (!mdVectorUsed[i]) {
                mdVectorUsed[i] = true;
                return mdVector[i];
            }
        }
        throw std::runtime_error("Pool exhausted");
    }

    void release(std::shared_ptr<T> MDReference) {
        std::lock_guard<std::mutex> lock(mtx);
        for (size_t i = 0; i < mdVector.size(); ++i) {
            if (MDReference == mdVector[i]) {
                mdVectorUsed[i] = false;
                return;
            }
        }
        throw std::invalid_argument("Invalid md object");
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return mdVector.size();
    }

    size_t usedSize() const {
        std::lock_guard<std::mutex> lock(mtx);
        size_t count = 0;
        for (bool used : mdVectorUsed) {
            if (used) count++;
        }
        return count;
    }

    void destroy() {
        std::lock_guard<std::mutex> lock(mtx);
        singlePool = nullptr;
    }
};

template <typename T>
std::shared_ptr<SinglePool<T>> SinglePool<T>::singlePool = nullptr;

template <typename T>
std::mutex SinglePool<T>::mtx;
