#include "ApplicationWinImp.h"
#include "Application/Application.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

ApplicationWinImp::ApplicationWinImp()
{
}

void ApplicationWinImp::RegisterAndCreateWindow(int width, int height, const char* windowName)
{
    auto hInst = ::GetModuleHandle(nullptr);

    WNDCLASSEX wc;

    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsg;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst,
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = WND_CLASS_NAME;
    wc.hIconSm = nullptr;

    ::RegisterClassExA(&wc);

    RECT rect;
    rect.left = 100;
    rect.right = width + rect.left;
    rect.top = 100;
    rect.bottom = height + rect.top;

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_SYSMENU;

    ::AdjustWindowRect(&rect, style, FALSE);

    // send self via WM_NCCREATE. build the relationship between instance pointer and win api.
    void* lParam = this;

    _hWnd = ::CreateWindowExA(
            0,
            WND_CLASS_NAME,
            windowName,
            style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            nullptr,
            nullptr,
            hInst,
            lParam
    );
}

void ApplicationWinImp::ShowWindow()
{
    ::ShowWindow(_hWnd, SW_SHOWDEFAULT);
}

void ApplicationWinImp::DestroyWindow()
{
    ::DestroyWindow(_hWnd);
}

void ApplicationWinImp::AddWinMsgProc(IWinMsgReceiver* pWinMsgReceiver)
{
    auto itr = std::find(_winMsgReceiverVec.begin(), _winMsgReceiverVec.end(), pWinMsgReceiver);
    if (itr == _winMsgReceiverVec.end())
        _winMsgReceiverVec.push_back(pWinMsgReceiver);
}

void ApplicationWinImp::RemoveWinMsgProc(IWinMsgReceiver* pWinMsgReceiver)
{
    auto itr = std::find(_winMsgReceiverVec.begin(), _winMsgReceiverVec.end(), pWinMsgReceiver);
    if (itr != _winMsgReceiverVec.end())
        _winMsgReceiverVec.erase(itr);
}

#pragma region [Windows Message]

LRESULT ApplicationWinImp::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application* pApp = Application::GetInstance();
    return pApp->_pImpl->HandleMsgDispatch(pApp, hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::HandleMsgDispatch(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    for (auto pWinMsgReceiver : _winMsgReceiverVec)
    {
        if (pWinMsgReceiver != nullptr)
        {
            pWinMsgReceiver->OnWinMsg(
                    reinterpret_cast<int64_t>(hWnd),
                    static_cast<uint32_t>(msg),
                    static_cast<int64_t>(wParam),
                    static_cast<int64_t>(lParam));
        }
    }

    switch (msg)
    {
        case WM_CLOSE:
            return OnMsgWmClose(pApp, hWnd, msg, wParam, lParam);
        case WM_SIZE:
            return OnMsgSize(pApp, hWnd, msg, wParam, lParam);
        case WM_KILLFOCUS:
            return OnMsgWmKillFocus(pApp, hWnd, msg, wParam, lParam);
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: // system key like 'alt'
            return OnMsgWmKeyDownAndSysKeyDown(pApp, hWnd, msg, wParam, lParam);
        case WM_KEYUP:
        case WM_SYSKEYUP:
            return OnMsgWmKeyUpAndSysKeyUp(pApp, hWnd, msg, wParam, lParam);
        case WM_CHAR:
            return OnMsgWmChar(pApp, hWnd, msg, wParam, lParam);
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
    Input::Keyboard::ClearState();

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgSize(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    pApp->_width = LOWORD(lParam);
    pApp->_height = HIWORD(lParam);

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmKeyDownAndSysKeyDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // if first press down, lParam & 0x40000000 = 1
    if (!(lParam & 0x40000000) || Input::Keyboard::IsAutoRepeatEnabled())
        Input::Keyboard::OnKeyPressed(static_cast<unsigned char>(wParam));

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmKeyUpAndSysKeyUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Input::Keyboard::OnKeyReleased(static_cast<unsigned char>(wParam));

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT ApplicationWinImp::OnMsgWmChar(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Input::Keyboard::OnCharW(static_cast<wchar_t>(wParam));

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
            Input::Mouse::OnMouseEnter();
        }
    } else
    {
        // 按住的时候离开窗口，不许离开
        // do not allow mouse leave this window when pressing
        if (wParam & (MK_LBUTTON | MK_RBUTTON | MK_MBUTTON))
        {
            Input::Mouse::OnMouseMove(pt.x, pt.y);
        } else
        {
            ::ReleaseCapture();
            Input::Mouse::OnMouseLeave();
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
    POINTS pt = MAKEPOINTS(lParam);
    Input::Mouse::OnWheelDelta(pt.x, pt.y, GET_WHEEL_DELTA_WPARAM(wParam));
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND ApplicationWinImp::GetWindowHandle() const
{
    return _hWnd;
}

#pragma endregion


