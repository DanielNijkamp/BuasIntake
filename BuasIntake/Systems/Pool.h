#pragma once
#include <deque>
#include <memory>

template <typename T>
class Pool {
public:
    virtual ~Pool() = default;
    
    std::shared_ptr<T> PopFront()
    {
        if (pool.empty())
            return nullptr;

        std::shared_ptr<T> ptr = std::move(pool.front());
        pool.pop_front();
        return ptr;
    }

    std::shared_ptr<T> PopBack()
    {
        if (pool.empty())
            return nullptr;

        std::shared_ptr<T> ptr = std::move(pool.back());
        pool.pop_back();
        return ptr;
    }

    void ReleaseBack(std::shared_ptr<T> ptr) {
        pool.push_back(std::move(ptr));
    }

    void ReleaseFront(std::shared_ptr<T> ptr) {
        pool.push_front(std::move(ptr));
    }

protected:
    std::deque<std::shared_ptr<T>> pool;
};
