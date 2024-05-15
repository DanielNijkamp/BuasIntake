#pragma once
#include <functional>
#include <vector>

/**
 * \brief
 * Poor man's multi-cast delegate event
 */
template<typename T = void>
class Event {
public:
    using Callback = std::function<void(T)>;
    
    void Subscribe(const Callback& callback) {
        callbacks.push_back(callback);
    }
    
    void Fire(T argument) const {
        for (const auto& callback : callbacks) {
            callback(argument);
        }
    }
    
private:
    std::vector<Callback> callbacks;
};

template<>
class Event<void> {
public:
    using Callback = std::function<void()>;
    
    void Subscribe(const Callback& callback) {
        callbacks.push_back(callback);
    }
    
    void Fire() const {
        for (const auto& callback : callbacks) {
            callback();
        }
    }
    
private:
    std::vector<Callback> callbacks;
};

