
#include "Application.h"
#include "RendererHardwareInterface/OpenGL/RenderCommand/RenderCommandOpenGL.h"
#include "Util/Logger/Logger.h"

Application::Application()
{
    Util::Logger::InitConsoleLogger();

    _pImpl = new ApplicationWinImp();
}

Application::~Application()
{
    for (auto pLooper : _loopLogic)
        delete pLooper;

    if (!_pRenderCommand)
        _pRenderCommand->Destroy();

    delete _pRenderCommand;

    DestroyWindow();

    delete _pImpl;
}

void Application::InitWindow(RendererApi api, int windowWidth, int windowHeight)
{
    _width = windowWidth;
    _height = windowHeight;

    _pImpl->RegisterAndCreateWindow(_width, _height, WINDOW_NAME);
    _pImpl->ShowWindow();

    _pRenderCommand = Renderer::RenderCommand::Create(api);
    _pRenderCommand->SetUp();
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

            _pRenderCommand->ClearColor(Eigen::Vector4f{0.2f, 0.2f, 0.2f, 1.0f});

            for (auto& looper : _loopLogic)
                looper->Loop();

            _pRenderCommand->SwapBuffer();
        }

        if (shouldStop)
            break;
    }
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

Renderer::RenderCommand* Application::GetRenderCommand()
{
    return _pRenderCommand;
}

void* Application::GetWindowHandle() const
{
    return reinterpret_cast<void*>(_pImpl->GetWindowHandle());
}

const Input::Keyboard& Application::GetKeyboard() const
{
    return _keyboard;
}

const Input::Mouse& Application::GetMouse() const
{
    return _mouse;
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


