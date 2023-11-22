#include "PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"
#include "Util/Logger/Logger.h"

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
        ::glCompileShader(_shaderId);

        GLint flag;
        GLchar infoLog[512];
        ::glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &flag);
        if (flag == GL_FALSE)
        {
            ::glGetShaderInfoLog(_shaderId, 512, nullptr, infoLog);
            Util::Logger::LogError(std::string("Shader Compile Fail: ") + infoLog);
            return false;
        }

        return true;
    }

    unsigned int PixelShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}