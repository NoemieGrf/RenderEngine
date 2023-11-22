#include "OpenGLHelper.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    bool OpenGLHelper::CompileShader(unsigned int shaderId)
    {
        ::glCompileShader(shaderId);

        GLint flag;
        GLchar infoLog[512];
        ::glGetShaderiv(shaderId, GL_COMPILE_STATUS, &flag);
        if (flag == GL_FALSE)
        {
            ::glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
            Util::Logger::LogError(std::string("Shader Compile Fail: ") + infoLog);
            return false;
        }

        return true;
    }
}