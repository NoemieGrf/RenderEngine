#include "PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Utility/OpenGLUtility.h"

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
        _needCompile = true;
    }

    void PixelShaderOpenGL::LoadFromBinaray(const char* data, int size)
    {
        _shaderId = ::glCreateShader(GL_FRAGMENT_SHADER);
        ::glShaderBinary(1, &_shaderId, GL_SHADER_BINARY_FORMAT_SPIR_V, data, size);
        ::glSpecializeShader(_shaderId, "main", 0, nullptr, nullptr);
        OpenUtility::CheckShaderState(_shaderId);

        _needCompile = false;
    }

    bool PixelShaderOpenGL::Compile()
    {
        if (!_needCompile)
            return true;

        ::glCompileShader(_shaderId);
        return OpenUtility::CheckShaderState(_shaderId);
    }
}