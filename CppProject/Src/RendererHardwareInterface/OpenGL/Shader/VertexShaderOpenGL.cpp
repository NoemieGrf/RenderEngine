#include "VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    VertexShaderOpenGL::~VertexShaderOpenGL()
    {
        ::glDeleteShader(_shaderId);
    }

    void VertexShaderOpenGL::LoadFromString(const char* data)
    {
        _shaderId = ::glCreateShader(GL_VERTEX_SHADER);
        ::glShaderSource(_shaderId, 1, &data, nullptr);
    }

    bool VertexShaderOpenGL::Compile()
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

    unsigned int VertexShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}