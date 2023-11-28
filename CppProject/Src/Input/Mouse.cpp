
#include "assert.h"
#include "Mouse.h"
#include "Util/Util.hpp"

namespace Input
{
    Mouse::Event::Event(Mouse::EventType t, int x, int y)
        : eventType(t)
        , x(x)
        , y(y)
    {
    }

    Mouse::ButtonEvent::ButtonEvent(Mouse::EventType t, MouseButton btn, int x, int y, bool down)
        : Event(t, x, y)
        , mouseButton(btn)
        , isDown(down)
    {
    }

    Mouse::WheelEvent::WheelEvent(Mouse::EventType t, int x, int y, bool up, int delta)
            : Event(t, x, y)
            , isUp(up)
            , wheelDelta(delta)
    {
    }

    void Mouse::ProcessEvent()
    {
        std::fill(_buttonPressing.begin(), _buttonPressing.end(), false);
        std::fill(_buttonReleasing.begin(), _buttonReleasing.end(), false);
        _wheelScrollingUp = false;
        _wheelScrollingDown = false;
        _wheelDelta = 0;

        while (!_eventQueue.empty())
        {
            const auto& pEvent = _eventQueue.front();

            _x = pEvent->x;
            _y = pEvent->y;

            switch (pEvent->eventType)
            {
                case EventType::Move:
                {
                    break;
                }
                case EventType::Button:
                {
                    Ptr<const ButtonEvent> pButtonEvent = DynamicCast<ButtonEvent>(pEvent);
                    assert(pButtonEvent != nullptr);

                    bool isDown = pButtonEvent->isDown;
                    if (isDown)
                    {
                        bool isNewPress = !_buttonState[(int)pButtonEvent->mouseButton];

                        _buttonState[(int)pButtonEvent->mouseButton] = true;

                        if (isNewPress)
                            _buttonPressing[(int)pButtonEvent->mouseButton] = true;
                    }
                    else
                    {
                        bool isNewRelease = _buttonState[(int)pButtonEvent->mouseButton];

                        _buttonState[(int)pButtonEvent->mouseButton] = false;

                        if (isNewRelease)
                            _buttonReleasing[(int)pButtonEvent->mouseButton] = true;
                    }
                    break;
                }
                case EventType::Wheel:
                {
                    Ptr<const WheelEvent> pWheelEvent = DynamicCast<WheelEvent>(pEvent);
                    assert(pWheelEvent != nullptr);

                    if (pWheelEvent->isUp)
                        _wheelScrollingUp = true;
                    else
                        _wheelScrollingDown = true;

                    _wheelDelta += pWheelEvent->wheelDelta;

                    break;
                }
                case EventType::Enter:
                {
                    _isMouseInWindow = true;
                    break;
                }
                case EventType::Leave:
                {
                    _isMouseInWindow = false;
                    break;
                }
            }

            _eventQueue.pop();
        }

    }

    void Mouse::Clear()
    {
        std::fill(_buttonPressing.begin(), _buttonPressing.end(), false);
        std::fill(_buttonReleasing.begin(), _buttonReleasing.end(), false);
        std::fill(_buttonState.begin(), _buttonState.end(), false);
        _wheelScrollingUp = false;
        _wheelScrollingDown = false;
        _wheelDelta = 0;

        while (!_eventQueue.empty())
            _eventQueue.pop();
    }

    std::pair<int, int> Mouse::GetPosition()
    {
        return {_x, _y};
    }

    int Mouse::GetPositionX()
    {
        return _x;
    }

    int Mouse::GetPositionY()
    {
        return _y;
    }

    bool Mouse::IsButtonDown(MouseButton button)
    {
        return _buttonState[(int)button];
    }

    bool Mouse::IsButtonPressing(MouseButton button)
    {
        return _buttonPressing[(int)button];
    }

    bool Mouse::IsButtonReleasing(MouseButton button)
    {
        return _buttonReleasing[(int)button];
    }

    bool Mouse::IsInWindow()
    {
        return _isMouseInWindow;
    }

    void Mouse::OnMouseMove(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<Event>(EventType::Move, x, y));
    }

    void Mouse::OnLeftMousePressed(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<ButtonEvent>(EventType::Move, MouseButton::Left, x, y, true));
    }

    void Mouse::OnLeftMouseReleased(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<ButtonEvent>(EventType::Move, MouseButton::Left, x, y, false));
    }

    void Mouse::OnMiddleMousePressed(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<ButtonEvent>(EventType::Move, MouseButton::Middle, x, y, true));
    }

    void Mouse::OnMiddleMouseReleased(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<ButtonEvent>(EventType::Move, MouseButton::Middle, x, y, false));
    }

    void Mouse::OnRightMousePressed(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<ButtonEvent>(EventType::Move, MouseButton::Right, x, y, true));
    }

    void Mouse::OnRightMouseReleased(int x, int y)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<ButtonEvent>(EventType::Move, MouseButton::Right, x, y, false));
    }

    void Mouse::OnWheelDelta(int x, int y, int wheelDelta)
    {
        if (_eventQueue.size() >= EVENT_QUEUE_SIZE)
            return;

        _eventQueue.emplace(std::make_shared<WheelEvent>(EventType::Move, x, y, false, wheelDelta));
    }

    void Mouse::OnMouseEnter(int x, int y)
    {
        _eventQueue.emplace(std::make_shared<Event>(EventType::Enter, x, y));
    }

    void Mouse::OnMouseLeave(int x, int y)
    {
        _eventQueue.emplace(std::make_shared<Event>(EventType::Leave, x, y));
    }
}