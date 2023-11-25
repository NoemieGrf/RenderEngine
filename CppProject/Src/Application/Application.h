#pragma once

#include "AppLooper.h"
#include "Util/NonCopyable.h"
#include "Define/RendererApi.h"
#include "ApplicationWinImp/ApplicationWinImp.h"

class Application : public NonCopyable
{
public:
    friend class ApplicationWinImp;

public:
    ~Application();
    void InitWindow(RendererApi api, int windowWidth, int windowHeight);
    void DestroyWindow();
    void RunLoop();

    template<AppLooperImpl T, class... Types>
    void AddLooper(Types&&... Args)
    {
        AppLooper* pLooper = new T(std::forward<Types&&...>(Args...));
        _loopLogic.push_back(pLooper);
    }

    template<AppLooperImpl T>
    void AddLooper()
    {
        AppLooper* pLooper = new T();
        _loopLogic.push_back(pLooper);
    }

public: // Getter
    int GetWindowHeight() const;
    int GetWindowWidth() const;
    RendererApi GetRenderApi() const;
    void* GetWindowHandle() const;

private:
    Application();

private:
    /* imp */
    ApplicationWinImp* _pImpl = nullptr;

    /* Rhi */
    RendererApi _api = RendererApi::OpenGL;

    /* Basic */
    int _height = 0;
    int _width = 0;

    /* Looper */
    std::vector<AppLooper*> _loopLogic {};

private:
    inline static Application* _instance = nullptr;
    inline static constexpr const char* WINDOW_NAME = "Graphic Render";

public:
    static void CreateInstance();
    static Application* GetInstance();
};