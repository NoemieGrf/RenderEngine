#pragma once

#include <queue>
#include <array>
#include <unordered_set>

#include "Helper/NonConstructible.h"
#include "KeyCode.h"

class Application;
class ApplicationWinImp;

namespace Input
{
    class Keyboard : public Helper::NonConstructible
    {
    public:
        friend class ::Application;
        friend class ::ApplicationWinImp;

    private:
        enum class EventType
        {
            KeyDown,
            KeyUp
        };

        struct Event
        {
            EventType eventType;
            KeyCode keyCode;
        };

    public:
        static void ProcessEvent();
        static void Clear();

        static bool IsKeyDown(KeyCode keycode);
        static bool IsKeyPressing(KeyCode keycode);
        static bool IsKeyReleasing(KeyCode keycode);

    private:
        static void OnKeyPressed(KeyCode keycode);
        static void OnKeyReleased(KeyCode keycode);

    private:
        static constexpr unsigned int EVENT_QUEUE_SIZE = 64;

        inline static std::unordered_set<KeyCode> _pressingKey;
        inline static std::unordered_set<KeyCode> _releasingKey;
        inline static std::array<bool, static_cast<int>(KeyCode::Count)> _keyState;
        inline static std::queue<Event> _eventQueue;
    };
}
