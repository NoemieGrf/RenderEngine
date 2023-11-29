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
            const auto& topEvent = _eventQueue.front();

            if (topEvent.eventType == EventType::KeyDown)
            {
                bool isNewPress = !_keyState[(int)topEvent.keyCode];

                _keyState[(int)topEvent.keyCode] = true;

                if (isNewPress)
                    _pressingKey.insert(topEvent.keyCode);
            }
            else if (topEvent.eventType == EventType::KeyUp)
            {
                bool isNewRelease = _keyState[(int)topEvent.keyCode];

                _keyState[(int)topEvent.keyCode] = false;

                if (isNewRelease)
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

        std::fill(_keyState.begin(), _keyState.end(), false);
    }

    bool Keyboard::IsKeyDown(KeyCode keycode)
    {
        return _keyState[(int)keycode];
    }

    bool Keyboard::IsKeyPressing(KeyCode keycode)
    {
        return _pressingKey.find(keycode) != _pressingKey.end();
    }

    bool Keyboard::IsKeyReleasing(KeyCode keycode)
    {
        return _releasingKey.find(keycode) != _releasingKey.end();
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