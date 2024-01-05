#pragma once

#include <string>
#include "Define/WindowsPlatform.h"
#include "Helper/NonCopyable.h"

class Application;

class ApplicationWinImp : public Helper::NonCopyable
{
public:
    ApplicationWinImp();

public:
    HWND GetWindowHandle() const;
    void RegisterWin32Window();
    void ShowWin32Window(int width, int height, const std::wstring& windowName);
    void DestroyWindow();
    void UnRegisterWindow();
    LRESULT HandleMsgDispatch(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    static LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    /* System */
    LRESULT OnMsgWmClose(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmKillFocus(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgSize(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    /* Input */
    LRESULT OnMsgWmKeyCode(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMouseMove(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmLButtonDown(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmLButtonUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMButtonDown(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMButtonUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmRButtonDown(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmRButtonUp(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMouseWheel(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HWND _hWnd = nullptr;

private:
    static constexpr const wchar_t* WND_CLASS_NAME = L"Graphic Render";

};