#include <Helper/Logger.h>
#include "ShaderProgramOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Helper/OpenGLHelper.h"

namespace Renderer
{

    ShaderProgramOpenGL::ShaderProgramOpenGL()
        : ShaderProgram()
    {
        _shaderProgramId = ::glCreateProgram();
    }

    void ShaderProgramOpenGL::AttachShader(const Ptr<Shader>& pShader)
    {
        Ptr<IOpenGLShaderId> pOpenGLShader = DynamicCast<IOpenGLShaderId>(pShader);
        if (pOpenGLShader == nullptr)
        {
            Helper::Logger::LogWarn("Shader convert fail `{}` when attaching.", ShaderTypeHelper::ShaderTypeToString(pShader->GetShaderType()));
            return;
        }

        ::glAttachShader(_shaderProgramId, pOpenGLShader->GetShaderId());
    }

    bool ShaderProgramOpenGL::Compile()
    {
        for (const auto& pShader: _shaderArray)
        {
            if (pShader != nullptr)
                pShader->Compile();
        }

        ::glLinkProgram(_shaderProgramId);

        GLint success = false;
        ::glGetProgramiv(_shaderProgramId, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            Helper::Logger::LogError("Shader Link Fail: {}", OpenGLHelper::GetProgramInfoLog(_shaderProgramId));
            return false;
        }

        return true;
    }

    void ShaderProgramOpenGL::Bind()
    {
        ::glUseProgram(_shaderProgramId);
    }

    void ShaderProgramOpenGL::SetUniformInt(const std::string& name, int value)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform1i(location, value);
    }

    void ShaderProgramOpenGL::SetUniformUnsignedInt(const std::string& name, unsigned int value)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform1ui(location, value);
    }

    void ShaderProgramOpenGL::SetUniformFloat(const std::string& name, float value)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform1f(location, value);
    }

    void ShaderProgramOpenGL::SetUniformFloat2(const std::string& name, const Eigen::Vector2f& value)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform2f(location, value.x(), value.y());
    }

    void ShaderProgramOpenGL::SetUniformFloat3(const std::string& name, const Eigen::Vector3f& value)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform3f(location, value.x(), value.y(), value.z());
    }

    void ShaderProgramOpenGL::SetUniformFloat4(const std::string& name, const Eigen::Vector4f& value)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform4f(location, value.x(), value.y(), value.z(), value.w());
    }

    void ShaderProgramOpenGL::SetUniformMat3(const std::string& name, const Eigen::Matrix3f& mat)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        // Eigen is column major, so no need to transpose
        ::glUniformMatrix3fv(location, 1, GL_FALSE, mat.data());
    }

    void ShaderProgramOpenGL::SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat)
    {
        const GLint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        // Eigen is column major, so no need to transpose
        ::glUniformMatrix4fv(location, 1, GL_FALSE, mat.data());
    }
}