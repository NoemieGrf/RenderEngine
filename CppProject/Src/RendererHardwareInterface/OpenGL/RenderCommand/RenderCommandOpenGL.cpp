#include "RenderCommandOpenGL.h"
#include "Application/Application.h"
#include "Define/WindowsPlatform.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"

namespace Renderer
{
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
        auto pApplication = Application::GetInstance();
        HWND hWnd = reinterpret_cast<HWND>(pApplication->GetWindowHandle());

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

        ::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        ::glViewport(0, 0, pApplication->GetWindowHeight(), pApplication->GetWindowWidth());

        return true;
    }

    void RenderCommandOpenGL::Destroy()
    {
        ::wglMakeCurrent(nullptr, nullptr);
        ::wglDeleteContext(_pData->_hRC);

        HWND hWnd = reinterpret_cast<HWND>(Application::GetInstance()->GetWindowHandle());
        ::ReleaseDC(hWnd, _pData->_hDC);
    }

    void RenderCommandOpenGL::SwapBuffer()
    {
        ::SwapBuffers(_pData->_hDC);
    }

    void RenderCommandOpenGL::Submit(const Ptr<VertexArray>& pVertArray)
    {
        pVertArray->Bind();
        ::glDrawElements(
                GL_TRIANGLES,
                pVertArray->GetCurrentIndexBuffer()->GetIndicesCount(),
                GL_UNSIGNED_INT,
                nullptr);
    }

    const RhiOpenGLData* RenderCommandOpenGL::GetData() const
    {
        return _pData;
    }

}