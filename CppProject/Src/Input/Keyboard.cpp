#include "Keyboard.h"
#include "Util/Util.hpp"
#include "Util/Logger/Logger.h"
#include "Application/Application.h"

namespace Input
{

    void Keyboard::ProcessEvent()
    {
        _pressingKey.clear();
        _releasingKey.clear();

        while (!_eventQueue.empty())
        {
            const auto& topEvent = _eventQueue.front();

            if (topEvent.eventType == EventType::KeyDown)
            {
                _keyStateSet[topEvent.keyCode] = true;
                if (_pressingKey.find(topEvent.keyCode) == _pressingKey.end())
                    _pressingKey.insert(topEvent.keyCode);
            }
            else if (topEvent.eventType == EventType::KeyUp)
            {
                _keyStateSet[topEvent.keyCode] = false;
                if (_releasingKey.find(topEvent.keyCode) == _releasingKey.end())
                    _releasingKey.insert(topEvent.keyCode);
            }

            _eventQueue.pop();
        }
    }

    void Keyboard::Clear()
    {
        _pressingKey.clear();
        _releasingKey.clear();

        while (!_eventQueue.empty())
            _eventQueue.pop();

        std::fill(_keyStateSet.begin(), _keyStateSet.end(), false);
    }

    bool Keyboard::IsKeyPressed(KeyCode keycode)
    {
        return false;
    }

    bool Keyboard::IsKeyPressing(KeyCode keycode)
    {
        return false;
    }

    bool Keyboard::IsKeyReleased(KeyCode keycode)
    {
        return false;
    }

    bool Keyboard::IsKeyReleasing(KeyCode keycode)
    {
        return false;
    }

    void Keyboard::OnKeyPressed(KeyCode keycode)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(EventType::KeyDown, keycode);
    }

    void Keyboard::OnKeyReleased(KeyCode keycode)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(EventType::KeyUp, keycode);
    }

}