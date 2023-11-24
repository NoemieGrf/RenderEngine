#pragma once

#include <queue>
#include "Util/NonCopyable.h"

class Application;
class ApplicationWinImp;

namespace Input
{
    class Mouse: public NonCopyable
    {
    public:
        friend class ::Application;
        friend class ::ApplicationWinImp;

    public:
        Mouse() = delete;
        ~Mouse() = delete;
        Mouse(const Mouse& mouse) = delete;
        Mouse& operator= (const Mouse& mouse) = delete;

    public:
        class Event
        {
        public:
            enum class Type
            {
                Invalid,
                Move,
                LeftPress,
                LeftRelease,
                RightPress,
                RightRelease,
                WheelUp,
                WheelDown,
                MiddlePress,
                MiddleRelease,
                Enter,
                Leave
            };

        private:
            Type _type;
            int _x;
            int _y;

        public:
            Event();
            Event(Type t, int x, int y);

        public:
            bool IsValid() const;
            Type GetType() const;
            std::pair<int, int> GetPosition() const;
            int GetPositionX() const;
            int GetPositionY() const;
        };

    public:
        static std::pair<int, int> GetPosition();
        static int GetPositionX();
        static int GetPositionY();
        static bool IsLeftPressed();
        static bool IsMiddlePressed();
        static bool IsRightPressed();
        static bool IsInWindow();
        static Mouse::Event RaiseEvent();
        static bool IsEmpty();
        static void Clear();

    private:
        static void OnMouseMove(int x, int y);

        static void OnLeftMousePressed(int x, int y);
        static void OnLeftMouseReleased(int x, int y);

        static void OnMiddleMousePressed(int x, int y);
        static void OnMiddleMouseReleased(int x, int y);

        static void OnRightMousePressed(int x, int y);
        static void OnRightMouseReleased(int x, int y);

        static void OnWheelUp(int x, int y);
        static void OnWheelDown(int x, int y);
        static void OnWheelDelta(int x, int y, int wheelDelta);

        static void OnMouseEnter();
        static void OnMouseLeave();

    private:
        static constexpr unsigned int QUEUE_SIZE = 16;

    private:
        inline static int _x;
        inline static int _y;
        inline static bool _leftPressed;
        inline static bool _middlePressed;
        inline static bool _rightPressed;
        inline static int _wheelDelta;
        inline static bool _isMouseInWindow;
        inline static std::queue<Event> _buffer;
    };
}


