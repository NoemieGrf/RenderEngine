#include "Keyboard.h"
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
            const auto& [eventType, keyCode] = _eventQueue.front();
            if (eventType == EventType::KeyDown)
            {
                bool isNewPress = !_keyState[static_cast<int>(keyCode)];

                _keyState[static_cast<int>(keyCode)] = true;

                if (isNewPress)
                    _pressingKey.insert(keyCode);
            }
            else if (eventType == EventType::KeyUp)
            {
                bool isNewRelease = _keyState[static_cast<int>(keyCode)];

                _keyState[static_cast<int>(keyCode)] = false;

                if (isNewRelease)
                    _releasingKey.insert(keyCode);
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

        std::ranges::fill(_keyState, false);
    }

    bool Keyboard::IsKeyDown(KeyCode keycode)
    {
        return _keyState[static_cast<int>(keycode)];
    }

    bool Keyboard::IsKeyPressing(KeyCode keycode)
    {
        return _pressingKey.contains(keycode);
    }

    bool Keyboard::IsKeyReleasing(KeyCode keycode)
    {
        return _releasingKey.contains(keycode);
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