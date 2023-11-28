#include "ApplicationWinImp.h"
#include "Application/Application.h"
#include "Input/Keyboard.h"
#include "Input/KeyCode.h"
#include "Input/Mouse.h"
#include "Editor/Editor.h"

extern Input::KeyCode WinVirtualKeyToKeyCode(WPARAM wParam);

LRESULT ApplicationWinImp::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application* pApp = Application::GetInstance();
    return pApp->_pImpl->HandleMsgDispatch(pApp, hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::HandleMsgDispatch(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Editor::Environment::OnWinMsg(reinterpret_cast<int64_t>(hWnd),
                                  static_cast<uint32_t>(msg),
                                  static_cast<int64_t>(wParam),
                                  static_cast<int64_t>(lParam));

    switch (msg)
    {
        case WM_CLOSE:
            return OnMsgWmClose(pApp, hWnd, msg, wParam, lParam);
        case WM_SIZE:
            return OnMsgSize(pApp, hWnd, msg, wParam, lParam);
        case WM_KILLFOCUS:
            return OnMsgWmKillFocus(pApp, hWnd, msg, wParam, lParam);
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            return OnMsgWmKeyCode(pApp, hWnd, msg, wParam, lParam);
        case WM_MOUSEMOVE:
            return OnMsgWmMouseMove(pApp, hWnd, msg, wParam, lParam);
        case WM_LBUTTONDOWN:
            return OnMsgWmLButtonDown(pApp, hWnd, msg, wParam, lParam);
        case WM_LBUTTONUP:
            return OnMsgWmLButtonUp(pApp, hWnd, msg, wParam, lParam);
        case WM_MBUTTONDOWN:
            return OnMsgWmMButtonDown(pApp, hWnd, msg, wParam, lParam);
        case WM_MBUTTONUP:
            return OnMsgWmMButtonUp(pApp, hWnd, msg, wParam, lParam);
        case WM_RBUTTONDOWN:
            return OnMsgWmRButtonDown(pApp, hWnd, msg, wParam, lParam);
        case WM_RBUTTONUP:
            return OnMsgWmRButtonUp(pApp, hWnd, msg, wParam, lParam);
        case WM_MOUSEWHEEL:
            return OnMsgWmMouseWheel(pApp, hWnd, msg, wParam, lParam);
        default:
            return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

LRESULT ApplicationWinImp::OnMsgWmClose(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
    return 0;
}

LRESULT ApplicationWinImp::OnMsgWmKillFocus(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // if key down raises other window, then key up will not send here, so here must clear states
    Input::Keyboard::Clear();

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgSize(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    pApp->_width = LOWORD(lParam);
    pApp->_height = HIWORD(lParam);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmKeyCode(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

LRESULT ApplicationWinImp::OnMsgWmMouseMove(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);

    if (pt.x >= 0 && pt.x < pApp->_width && pt.y > 0 && pt.y < pApp->_height)
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

LRESULT ApplicationWinImp::OnMsgWmLButtonDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnLeftMousePressed(pt.x, pt.y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmLButtonUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnLeftMouseReleased(pt.x, pt.y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMButtonDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnMiddleMousePressed(pt.x, pt.y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMButtonUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnMiddleMouseReleased(pt.x, pt.y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmRButtonDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnRightMousePressed(pt.x, pt.y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmRButtonUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnRightMouseReleased(pt.x, pt.y);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmMouseWheel(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousewheel
    POINTS pt = MAKEPOINTS(lParam);
    int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
    Input::Mouse::OnWheelDelta(pt.x, pt.y, wheelDelta);
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND ApplicationWinImp::GetWindowHandle() const
{
    return _hWnd;
}