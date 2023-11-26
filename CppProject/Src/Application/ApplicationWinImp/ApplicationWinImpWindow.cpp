#include "ApplicationWinImp.h"
#include "Application/Application.h"

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


