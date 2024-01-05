#pragma once

#include <queue>
#include <array>

#include <Helper/NonConstructible.h>
#include "Define/Define.h"

class Application;
class ApplicationWinImp;

namespace Input
{
    enum class MouseButton : int
    {
        Left,
        Right,
        Middle,
        Num4,
        Num5,
        Count
    };

    class Mouse: public Helper::NonConstructible
    {
    public:
        friend class ::Application;
        friend class ::ApplicationWinImp;

    private:
        enum class EventType
        {
            Move,
            Button,
            Wheel,
            Enter,
            Leave
        };

        struct Event
        {
            EventType eventType;
            int x;
            int y;

            Event(EventType, int, int);
            virtual ~Event() = default;
        };

        struct ButtonEvent : Event
        {
            bool isDown;
            MouseButton mouseButton;

            ButtonEvent(EventType, MouseButton, int, int, bool);
        };

        struct WheelEvent : Event
        {
            bool isUp;
            int wheelDelta;

            WheelEvent(EventType, int, int, bool, int);
        };

    public:
        static void ProcessEvent();
        static void Clear();

        static std::pair<int, int> GetPosition();
        static int GetPositionX();
        static int GetPositionY();
        static bool IsButtonDown(MouseButton button);
        static bool IsButtonPressing(MouseButton button);
        static bool IsButtonReleasing(MouseButton button);
        static bool IsInWindow();

    private:
        static void OnMouseMove(int x, int y);
        static void OnLeftMousePressed(int x, int y);
        static void OnLeftMouseReleased(int x, int y);
        static void OnMiddleMousePressed(int x, int y);
        static void OnMiddleMouseReleased(int x, int y);
        static void OnRightMousePressed(int x, int y);
        static void OnRightMouseReleased(int x, int y);
        static void OnWheelDelta(int x, int y, int wheelDelta);
        static void OnMouseEnter(int x, int y);
        static void OnMouseLeave(int x, int y);

    private:
        static constexpr unsigned int EVENT_QUEUE_SIZE = 64;

        inline static int _x;
        inline static int _y;
        inline static bool _wheelScrollingUp;
        inline static bool _wheelScrollingDown;
        inline static int _wheelDelta;
        inline static bool _isMouseInWindow = true;

        inline static std::array<bool, static_cast<int>(MouseButton::Count)> _buttonState;
        inline static std::array<bool, static_cast<int>(MouseButton::Count)> _buttonPressing;
        inline static std::array<bool, static_cast<int>(MouseButton::Count)> _buttonReleasing;

        inline static std::queue<Ptr<Event>> _eventQueue;
    };
}


