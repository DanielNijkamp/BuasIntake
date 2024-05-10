#pragma once

#include <unordered_map>
#include <unordered_set>
#include <SFML/Window/Keyboard.hpp>
#include "Event.h"

//event for input could also be generic since you might want to use pass the input itself like a vector 2 or something
//but since we just want to fire an event when a key is pressed and nothing more using void will suffice

class Input final
{
public:
    bool canProcessInputs = true;
    using Key = sf::Keyboard::Key;

    //we could also implement a method to act similarly to onButtonDown where the event only fires once and not continuously
    
    void SubscribeToContinuousKey(Key key, const Event<>::Callback& callback);
    void ProcessInputs();

private:
    std::unordered_map<Key, Event<>> keyEvents;
    std::unordered_set<Key> continuousKeys;
    
    void ProcessEvent(Key key);
    Event<>& GetOrCreateEvent(Key key);
};


