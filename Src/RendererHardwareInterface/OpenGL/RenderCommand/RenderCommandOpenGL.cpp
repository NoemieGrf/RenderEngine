#include <Helper/Logger.h>
#include <Helper/WinApi/WinApiWindow.h>
#include "RenderCommandOpenGL.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"

namespace Renderer
{
    static void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        std::string messageSource;
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            messageSource = "OpenGL";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            messageSource = "Windows";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            messageSource = "Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            messageSource = "Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            messageSource = "Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
        default:
            messageSource = "Other";
            break;
        }

        std::string messageType;
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            messageType = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            messageType = "Deprecated Behavior";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            messageType = "Undefined Behavior";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            messageType = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            messageType = "Performance";
            break;
        case GL_DEBUG_TYPE_OTHER:
        default:
            messageType = "Other";
            break;
        }

        std::string messageSeverity;
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            messageSeverity = "High";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            messageSeverity = "Medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            messageSeverity = "Low";
            break;
        default:
            messageSeverity = "Other";
            break;
        }

        if (type == GL_DEBUG_TYPE_ERROR)
            Helper::Logger::LogError("[GLErrorCallback][{}][{}][{}] {}", messageSource, messageType, messageSeverity, message);
        else
            Helper::Logger::LogWarn("[GLErrorCallback][{}][{}][{}] {}", messageSource, messageType, messageSeverity, message);
    }

    void RenderCommandOpenGL::ClearColor(const Eigen::Vector4f& color)
    {
        glClearColor(color.x(), color.y(), color.z(), color.w());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    RenderCommandOpenGL::RenderCommandOpenGL()
        : _hDeviceConext(nullptr)
        , _hRenderContext(nullptr)
    {
    }

    bool RenderCommandOpenGL::SetUp()
    {
        void* hWnd = Application::GetWindowHandle();
        auto setFormatSuccess = Helper::Win::Window::OpenGL::PrepareWindowPixelFormat(hWnd);
        if (!setFormatSuccess)
            return false;

        _hDeviceConext = Helper::Win::Window::GetDeviceContext(hWnd);
        _hRenderContext = Helper::Win::Window::OpenGL::CreateRenderContext(_hDeviceConext);

        auto makeContextSuccess = Helper::Win::Window::OpenGL::BindRenderContext(_hDeviceConext, _hRenderContext);
        if (!makeContextSuccess)
        {
            Helper::Win::Window::OpenGL::BindRenderContext(nullptr, nullptr);
            Helper::Win::Window::OpenGL::DestroyRenderContext(_hRenderContext);
            return false;
        }

        // init glad
        auto gladSuccess = ::gladLoadGL();
        if (!gladSuccess)
        {
            Helper::Win::Window::OpenGL::BindRenderContext(nullptr, nullptr);
            Helper::Win::Window::OpenGL::DestroyRenderContext(_hRenderContext);
            return false;
        }

        // set gl error callback
        ::glEnable(GL_DEBUG_OUTPUT);
        ::glDebugMessageCallback(&DebugMessageCallback, nullptr);

        // version
        Helper::Logger::LogInfo("OpenGL Version: {}", reinterpret_cast<const char*>(::glGetString(GL_VERSION)));
        Helper::Logger::LogInfo("OpenGL Vendor: {}", reinterpret_cast<const char*>(::glGetString(GL_VENDOR)));
        Helper::Logger::LogInfo("OpenGL Renderer: {}", reinterpret_cast<const char*>(::glGetString(GL_RENDERER)));
        Helper::Logger::LogInfo("OpenGL Shader Version: {}", reinterpret_cast<const char*>(::glGetString(GL_SHADING_LANGUAGE_VERSION)));

        // set viewport
        ::glViewport(0, 0, Application::GetWindowHeight(), Application::GetWindowWidth());

        // enable opengl blend
        ::glEnable(GL_BLEND);
        ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // enable depth test
        ::glEnable(GL_DEPTH_TEST);

        // cull face
        ::glCullFace(GL_BACK);

        return true;
    }

    void RenderCommandOpenGL::Destroy()
    {
        void* hWnd = Application::GetWindowHandle();
        Helper::Win::Window::OpenGL::BindRenderContext(nullptr, nullptr);
        Helper::Win::Window::OpenGL::DestroyRenderContext(_hRenderContext);
        Helper::Win::Window::ReleaseDeviceContext(hWnd, _hDeviceConext);
    }

    void RenderCommandOpenGL::SwapBuffer()
    {
        Helper::Win::Window::DeviceContextSwapBuffer(_hDeviceConext);
    }

    void RenderCommandOpenGL::Submit(RendererPassType pass, const Ptr<InputAssemble>& pInputAssemble, const Ptr<Material>& pMaterial)
    {
        pInputAssemble->Bind();
        pMaterial->Bind(pass);
        pMaterial->SetUniform(pass);
        ::glDrawElements(
                GL_TRIANGLES,
                pInputAssemble->GetIndexBuffer()->GetIndicesCount(),
                GL_UNSIGNED_INT,
                nullptr);
    }

    const void* RenderCommandOpenGL::GetDeviceContextHandle() const
    {
        return _hDeviceConext;
    }

    const void* RenderCommandOpenGL::GetRenderCoontextHandle() const
    {
        return _hRenderContext;
    }

}