#include "ApplicationWinImp.h"
#include "Helper/WinApi/WinApiWindow.h"

ApplicationWinImp::ApplicationWinImp()
{
}

void ApplicationWinImp::RegisterWin32Window()
{
    Helper::Win::Window::RegisterInfo registerInfo {};
    registerInfo.hIcon = nullptr;
    registerInfo.hIconSmall = nullptr;
    registerInfo.hCursor = nullptr;
    registerInfo.pWinMsgProc = reinterpret_cast<void*>(&HandleMsg);

    Helper::Win::Window::Register(WND_CLASS_NAME, registerInfo);
}

void ApplicationWinImp::ShowWin32Window(int width, int height, const std::wstring& windowName)
{
    Helper::Win::Window::StyleInfo style {};
    style.canResize = true;
    style.hasSysmenu = true;
    style.hasMaxBtn = false;
    style.hasMinBtn = false;

    // send self via WM_NCCREATE. build the relationship between instance pointer and win api.
    void* lParam = this;

    Helper::Win::Window::Show(WND_CLASS_NAME, windowName, width, height, style, lParam);
}

void ApplicationWinImp::DestroyWindow()
{
    Helper::Win::Window::Destroy(_hWnd);
}

void ApplicationWinImp::UnRegisterWindow()
{
    Helper::Win::Window::UnRegister(WND_CLASS_NAME);
}


