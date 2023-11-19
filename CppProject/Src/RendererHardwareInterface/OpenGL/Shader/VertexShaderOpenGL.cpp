#include "VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    VertexShaderOpenGL::~VertexShaderOpenGL()
    {
        ::glDeleteShader(_shaderId);
    }

    bool VertexShaderOpenGL::LoadFromString(const char* data)
    {
        _shaderId = ::glCreateShader(GL_VERTEX_SHADER);
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

    bool VertexShaderOpenGL::Compile()
    {
        ::glCompileShader(_shaderId);
        GLint vsSuccess = false;
        ::glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &vsSuccess);
        return vsSuccess;
    }

    unsigned int VertexShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}