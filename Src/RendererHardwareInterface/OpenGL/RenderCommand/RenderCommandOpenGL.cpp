#include "RenderCommandOpenGL.h"
#include "Application/Application.h"
#include "Define/WindowsPlatform.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{
    static void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        Util::Logger::LogError("Source {}, type {}, id {}, severity {}, length {}, {}", source, type, id, severity, length, message);
    }

    void RenderCommandOpenGL::ClearColor(const Eigen::Vector4f& color)
    {
        glClearColor(color.x(), color.y(), color.z(), color.w());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    RenderCommandOpenGL::RenderCommandOpenGL()
    {
        _pData = new RhiOpenGLData();
    }

    RenderCommandOpenGL::~RenderCommandOpenGL()
    {
        delete _pData;
    }

    bool RenderCommandOpenGL::SetUp()
    {
        HWND hWnd = static_cast<HWND>(Application::GetWindowHandle());

        // init openGL pixel format
        PIXELFORMATDESCRIPTOR pfd =
                {
                        sizeof(PIXELFORMATDESCRIPTOR),
                        1,
                        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
                        PFD_TYPE_RGBA,        // The kind of framebuffer.
                        32,                   // Color depth of the framebuffer.
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        0,
                        24,
                        8,
                        0
                };

        _pData->_hDC = ::GetDC(hWnd);
        GLuint pixelFormat = ::ChoosePixelFormat(_pData->_hDC, &pfd);
        auto setFormatSuccess = ::SetPixelFormat(_pData->_hDC, pixelFormat, &pfd);
        if (!setFormatSuccess)
            return false;

        // create opengl renderer context
        _pData->_hRC = ::wglCreateContext(_pData->_hDC);
        auto makeContextSuccess = ::wglMakeCurrent(_pData->_hDC, _pData->_hRC);
        if (!makeContextSuccess)
        {
            ::wglMakeCurrent(nullptr, nullptr);
            ::wglDeleteContext(_pData->_hRC);
            return false;
        }

        // init glad
        auto gladSuccess = ::gladLoadGL();
        if (!gladSuccess)
        {
            ::wglMakeCurrent(nullptr, nullptr);
            ::wglDeleteContext(_pData->_hRC);
            return false;
        }

        // set gl error callback
        ::glDebugMessageCallback(&DebugMessageCallback, nullptr);

        // version
        Util::Logger::LogInfo("OpenGL Version: {}", reinterpret_cast<const char*>(::glGetString(GL_VERSION)));
        Util::Logger::LogInfo("OpenGL Vendor: {}", reinterpret_cast<const char*>(::glGetString(GL_VENDOR)));
        Util::Logger::LogInfo("OpenGL Renderer: {}", reinterpret_cast<const char*>(::glGetString(GL_RENDERER)));
        Util::Logger::LogInfo("OpenGL Shader Version: {}", reinterpret_cast<const char*>(::glGetString(GL_SHADING_LANGUAGE_VERSION)));

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
        ::wglMakeCurrent(nullptr, nullptr);
        ::wglDeleteContext(_pData->_hRC);

        HWND hWnd = static_cast<HWND>(Application::GetWindowHandle());
        ::ReleaseDC(hWnd, _pData->_hDC);
    }

    void RenderCommandOpenGL::SwapBuffer()
    {
        ::SwapBuffers(_pData->_hDC);
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

    const RhiOpenGLData* RenderCommandOpenGL::GetData() const
    {
        return _pData;
    }

}