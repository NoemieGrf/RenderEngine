
#include "Application.h"
#include "Util/Logger/Logger.h"
#include "Renderer/RenderCommand/RenderCommand.h"

Application::Application()
{
    Util::Logger::InitConsoleLogger();

    _pImpl = new ApplicationWinImp();
}

Application::~Application()
{
    for (auto pLooper : _loopLogic)
        delete pLooper;

    Renderer::RenderCommand::Destroy();

    DestroyWindow();

    delete _pImpl;
}

void Application::InitWindow(RendererApi api, int windowWidth, int windowHeight)
{
    _width = windowWidth;
    _height = windowHeight;

    _pImpl->RegisterAndCreateWindow(_width, _height, WINDOW_NAME);
    _pImpl->ShowWindow();

    Renderer::RenderCommand::Init();
}

void Application::DestroyWindow()
{
    _pImpl->DestroyWindow();
}

void Application::RunLoop()
{
    while (true)
    {
        MSG msg;
        bool shouldStop = false;
        while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                shouldStop = true;
                break;
            }

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            Renderer::RenderCommand::ClearColor(Eigen::Vector4f{0.2f, 0.2f, 0.2f, 1.0f});

            for (auto& looper : _loopLogic)
                looper->Loop();

            Renderer::RenderCommand::SwapBuffer();
        }

        if (shouldStop)
            break;
    }
}

void Application::AddWinMsgProc(IWinMsgReceiver* pWinMsgReceiver)
{
    _pImpl->AddWinMsgProc(pWinMsgReceiver);
}

void Application::RemoveWinMsgProc(IWinMsgReceiver* pWinMsgReceiver)
{
    _pImpl->RemoveWinMsgProc(pWinMsgReceiver);
}

#pragma region [Getter]

int Application::GetWindowHeight() const
{
    return _width;
}

int Application::GetWindowWidth() const
{
    return _height;
}

RendererApi Application::GetRenderApi() const
{
    return _api;
}

void* Application::GetWindowHandle() const
{
    return reinterpret_cast<void*>(_pImpl->GetWindowHandle());
}

#pragma endregion

#pragma region [Static Instance]

void Application::CreateInstance()
{
    if (_instance == nullptr)
        _instance = new Application();
}

Application* Application::GetInstance()
{
    return _instance;
}

#pragma endregion


