#include "PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    PixelShaderOpenGL::~PixelShaderOpenGL()
    {
        ::glDeleteShader(_shaderId);
    }

    bool PixelShaderOpenGL::LoadFromString(const char* data)
    {
        _shaderId = ::glCreateShader(GL_FRAGMENT_SHADER);
        ::glShaderSource(_shaderId, 1, &data, nullptr);

        GLint flag;
        GLchar infoLog[512];
        glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &flag);
        if (!flag)
        {
            glGetShaderInfoLog(_shaderId, 512, nullptr, infoLog);
            Util::Logger::LogError(std::string("Shader Compile Fail, ") + infoLog);
            return false;
        }

        return true;
    }

    bool PixelShaderOpenGL::Compile()
    {
        ::glCompileShader(_shaderId);
        GLint vsSuccess = false;
        ::glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &vsSuccess);
        return vsSuccess;
    }

    unsigned int PixelShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}