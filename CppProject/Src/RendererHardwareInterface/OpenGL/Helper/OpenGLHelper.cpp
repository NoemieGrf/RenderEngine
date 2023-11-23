#include "OpenGLHelper.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{
    GLenum OpenGLHelper::GetShaderDataTypeGlEnum(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::None:
                return GL_FLOAT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Matrix3x3:
            case ShaderDataType::Matrix4x4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
        }

        return GL_FLOAT;
    }

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