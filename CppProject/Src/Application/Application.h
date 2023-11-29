#pragma once

#include "AppLooper.h"
#include "Util/NonConstructible.h"
#include "Define/RendererApi.h"
#include "ApplicationWinImp/ApplicationWinImp.h"

class Application : public NonConstructible
{
public:
    friend class ApplicationWinImp;

public:
    static void InitWindow(RendererApi api, int windowWidth, int windowHeight);
    static void DestroyWindow();
    static void RunLoop();

    template<AppLooperImpl T, class... Types>
    static void AddLooper(Types&&... Args)
    {
        AppLooper* pLooper = new T(std::forward<Types&&...>(Args...));
        _loopLogic.push_back(pLooper);
    }

    template<AppLooperImpl T>
    static void AddLooper()
    {
        AppLooper* pLooper = new T();
        _loopLogic.push_back(pLooper);
    }

public: // Getter
    static int GetWindowHeight();
    static int GetWindowWidth();
    static RendererApi GetRenderApi();
    static void* GetWindowHandle();
    static uint64_t GetFrameCount();

private:
    static void UpdateTime();
    static void UpdateInput();
    static void UpdateRender();
    static void WaitForTargetFrame();

private:
    /* Imp */
    inline static ApplicationWinImp* _pImpl = nullptr;

    /* Rhi */
    inline static RendererApi _api = RendererApi::OpenGL;

    /* Basic */
    inline static int _height = 0;
    inline static int _width = 0;
    inline static uint64_t _frameCount = 0;

    /* Looper */
    inline static std::vector<AppLooper*> _loopLogic {};

    /* Const */
    inline static constexpr const char* WINDOW_NAME = "Graphic Render";

};