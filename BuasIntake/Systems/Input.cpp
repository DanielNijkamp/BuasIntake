#include "Input.h"


Event<>& Input::GetOrCreateEvent(Key key)
{
    auto const it = keyEvents.find(key);
    if (it == keyEvents.end()) {
        return keyEvents[key] = Event<>();
    }
    return it->second;
}


void Input::SubscribeToContinuousKey(Key key, const Event<>::Callback& callback)
{
    GetOrCreateEvent(key).Subscribe(callback);
    continuousKeys.insert(key); 
}
void Input::ProcessInputs()
{
    if (!canProcessInputs || !focussed) {
        return;
    }
    
    for (auto key : continuousKeys) {
        if (sf::Keyboard::isKeyPressed(key)) {
            ProcessEvent(key);
        }
    }
}

void Input::ProcessEvent(Key key)
{
    auto it = keyEvents.find(key);
    if (it != keyEvents.end()) {
        it->second.Fire();
    }
}

