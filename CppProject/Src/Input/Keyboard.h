#pragma once

#include <queue>
#include <array>
#include <unordered_set>

#include "Util/NonConstructible.h"
#include "KeyCode.h"

class Application;
class ApplicationWinImp;

namespace Input
{
    class Keyboard : public NonConstructible
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

        static bool IsKeyPressed(KeyCode keycode);
        static bool IsKeyPressing(KeyCode keycode);
        static bool IsKeyReleased(KeyCode keycode);
        static bool IsKeyReleasing(KeyCode keycode);

    private:
        static void OnKeyPressed(KeyCode keycode);
        static void OnKeyReleased(KeyCode keycode);

    private:
        static constexpr unsigned int EVENT_QUEUE_SIZE = 64;

        inline static std::unordered_set<KeyCode> _pressingKey;
        inline static std::unordered_set<KeyCode> _releasingKey;
        inline static std::array<bool, KeyCode::Count> _keyStateSet;
        inline static std::queue<Event> _eventQueue;
    };
}
