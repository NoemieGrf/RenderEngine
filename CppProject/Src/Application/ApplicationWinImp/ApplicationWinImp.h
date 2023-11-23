#pragma once

#include <vector>
#include "IWinMsgReceiver.h"
#include "Define/WindowsPlatform.h"
#include "Util/NonCopyable.h"

class Application;

class ApplicationWinImp : public NonCopyable
{
public:
    ApplicationWinImp();

public:
    HWND GetWindowHandle() const;
    void RegisterAndCreateWindow(int width, int height, const char* windowName);
    void ShowWindow();
    void DestroyWindow();
    void AddWinMsgProc(IWinMsgReceiver* pWinMsgReceiver);
    void RemoveWinMsgProc(IWinMsgReceiver* pWinMsgReceiver);
    LRESULT HandleMsgDispatch(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    static LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    /* System */
    LRESULT OnMsgWmClose(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmKillFocus(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgSize(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    /* Input - Keyboard */
    LRESULT OnMsgWmKeyDownAndSysKeyDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmKeyUpAndSysKeyUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmChar(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    /* Input - Mouse */
    LRESULT OnMsgWmMouseMove(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmLButtonDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmLButtonUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMButtonDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMButtonUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmRButtonDown(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmRButtonUp(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT OnMsgWmMouseWheel(Application* pApp, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    HWND _hWnd = nullptr;

    /* Msg Receive */
    std::vector<IWinMsgReceiver*> _winMsgReceiverVec;

private:
    static constexpr const char* WND_CLASS_NAME = "Graphic Render";

};