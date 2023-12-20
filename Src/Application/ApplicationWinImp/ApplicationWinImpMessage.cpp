#include "ApplicationWinImp.h"
#include "Application/Application.h"
#include "Input/Keyboard.h"
#include "Input/KeyCode.h"
#include "Input/Mouse.h"
#include "Editor/Editor.h"

extern Input::KeyCode WinVirtualKeyToKeyCode(WPARAM wParam);

LRESULT ApplicationWinImp::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return Application::_pImpl->HandleMsgDispatch(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::HandleMsgDispatch(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Editor::Environment::OnWinMsg(reinterpret_cast<int64_t>(hWnd),
                                  static_cast<uint32_t>(msg),
                                  static_cast<int64_t>(wParam),
                                  static_cast<int64_t>(lParam));

    switch (msg)
    {
        case WM_CLOSE:
            return OnMsgWmClose(hWnd, msg, wParam, lParam);
        case WM_SIZE:
            return OnMsgSize(hWnd, msg, wParam, lParam);
        case WM_KILLFOCUS:
            return OnMsgWmKillFocus(hWnd, msg, wParam, lParam);
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            return OnMsgWmKeyCode(hWnd, msg, wParam, lParam);
        case WM_MOUSEMOVE:
            return OnMsgWmMouseMove(hWnd, msg, wParam, lParam);
        case WM_LBUTTONDOWN:
            return OnMsgWmLButtonDown(hWnd, msg, wParam, lParam);
        case WM_LBUTTONUP:
            return OnMsgWmLButtonUp(hWnd, msg, wParam, lParam);
        case WM_MBUTTONDOWN:
            return OnMsgWmMButtonDown(hWnd, msg, wParam, lParam);
        case WM_MBUTTONUP:
            return OnMsgWmMButtonUp(hWnd, msg, wParam, lParam);
        case WM_RBUTTONDOWN:
            return OnMsgWmRButtonDown(hWnd, msg, wParam, lParam);
        case WM_RBUTTONUP:
            return OnMsgWmRButtonUp(hWnd, msg, wParam, lParam);
        case WM_MOUSEWHEEL:
            return OnMsgWmMouseWheel(hWnd, msg, wParam, lParam);
        default:
            return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

LRESULT ApplicationWinImp::OnMsgWmClose(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
    return 0;
}

LRESULT ApplicationWinImp::OnMsgWmKillFocus(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // if key down raises other window, then key up will not send here, so here must clear states
    Input::Keyboard::Clear();

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgSize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application::_width = LOWORD(lParam);
    Application::_height = HIWORD(lParam);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmKeyCode(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    bool isDown = msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN;

    Input::KeyCode code;

    // Special case, keypad enter has no virtual code
    if ((wParam == VK_RETURN) && (HIWORD(lParam) & KF_EXTENDED))
        code = Input::KeyCode::KeypadEnter;
    else
        code = WinVirtualKeyToKeyCode(wParam);

    if (isDown)
        Input::Keyboard::OnKeyPressed(code);
    else
        Input::Keyboard::OnKeyReleased(code);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMouseMove(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);

    if (pt.x >= 0 && pt.x < Application::_width && pt.y > 0 && pt.y < Application::_height)
    {
        Input::Mouse::OnMouseMove(pt.x, pt.y);
        if (!Input::Mouse::IsInWindow())
        {
            ::SetCapture(_hWnd);
            Input::Mouse::OnMouseEnter(pt.x, pt.y);
        }
    } else
    {
        // do not allow mouse leave this window when pressing
        if (wParam & (MK_LBUTTON | MK_RBUTTON | MK_MBUTTON))
        {
            Input::Mouse::OnMouseMove(pt.x, pt.y);
        } else
        {
            ::ReleaseCapture();
            Input::Mouse::OnMouseLeave(pt.x, pt.y);
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmLButtonDown(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto [x, y] = MAKEPOINTS(lParam);
    Input::Mouse::OnLeftMousePressed(x, y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmLButtonUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto [x, y] = MAKEPOINTS(lParam);
    Input::Mouse::OnLeftMouseReleased(x, y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMButtonDown(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto [x, y] = MAKEPOINTS(lParam);
    Input::Mouse::OnMiddleMousePressed(x, y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMButtonUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto [x, y] = MAKEPOINTS(lParam);
    Input::Mouse::OnMiddleMouseReleased(x, y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmRButtonDown(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto [x, y] = MAKEPOINTS(lParam);
    Input::Mouse::OnRightMousePressed(x, y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmRButtonUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    auto [x, y] = MAKEPOINTS(lParam);
    Input::Mouse::OnRightMouseReleased(x, y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMouseWheel(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousewheel
    auto [x, y] = MAKEPOINTS(lParam);
    int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
    Input::Mouse::OnWheelDelta(x, y, wheelDelta);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND ApplicationWinImp::GetWindowHandle() const
{
    return _hWnd;
}