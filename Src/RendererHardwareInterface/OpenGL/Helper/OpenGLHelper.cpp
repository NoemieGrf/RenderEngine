#include "OpenGLHelper.h"
#include <Helper/Logger.h>

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

    bool OpenGLHelper::CheckShaderState(unsigned int shaderId)
    {
        GLint flag;
        ::glGetShaderiv(shaderId, GL_COMPILE_STATUS, &flag);
        if (flag == GL_FALSE)
        {
            Helper::Logger::LogError("Shader State Fail: {}", GetShaderInfoLog(shaderId));
            return false;
        }

        return true;
    }

    std::string OpenGLHelper::GetShaderInfoLog(unsigned int shaderId)
    {
        CheckInfoBuffer();

        ::glGetShaderInfoLog(shaderId, 512, nullptr, _pInfoLogBuffer);

        return std::string{ _pInfoLogBuffer };
    }

    std::string OpenGLHelper::GetProgramInfoLog(unsigned int programId)
    {
        CheckInfoBuffer();

        ::glGetProgramInfoLog(programId, 512, nullptr, _pInfoLogBuffer);

        return std::string{ _pInfoLogBuffer };
    }

    void OpenGLHelper::CheckInfoBuffer()
    {
        if (_pInfoLogBuffer == nullptr)
            _pInfoLogBuffer = new char[GL_INFO_BUFFER_SIZE];
    }
}