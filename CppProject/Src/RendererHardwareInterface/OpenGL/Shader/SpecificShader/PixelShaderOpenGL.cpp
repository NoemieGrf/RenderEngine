#include "PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Helper/OpenGLHelper.h"

namespace Renderer
{
    PixelShaderOpenGL::~PixelShaderOpenGL()
    {
        ::glDeleteShader(_shaderId);
    }

    void PixelShaderOpenGL::LoadFromString(const char* data)
    {
        _shaderId = ::glCreateShader(GL_FRAGMENT_SHADER);
        ::glShaderSource(_shaderId, 1, &data, nullptr);
    }

    bool PixelShaderOpenGL::Compile()
    {
        return OpenGLHelper::CompileShader(_shaderId);
    }

    unsigned int PixelShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}