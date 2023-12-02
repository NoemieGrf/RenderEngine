#include "ShaderProgramOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Helper/OpenGLHelper.h"
#include "Util/Logger/Logger.h"

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
            Util::Logger::LogWarn("Shader convert fail `{}` when attaching.", ShaderTypeHelper::ShaderTypeToString(pShader->GetShaderType()));
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
            Util::Logger::LogError("Shader Link Fail: {}", OpenGLHelper::GetProgramInfoLog(_shaderProgramId));
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
        GLuint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform1i(location, value);
    }

    void ShaderProgramOpenGL::SetUniformUnsignedInt(const std::string& name, unsigned int value)
    {
        GLuint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform1ui(location, value);
    }

    void ShaderProgramOpenGL::SetUniformFloat(const std::string& name, float value)
    {
        GLuint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniform1f(location, value);
    }

    void ShaderProgramOpenGL::SetUniformMat3(const std::string& name, const Eigen::Matrix3f& mat)
    {
        GLuint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniformMatrix3fv(location, 1, GL_FALSE, mat.data());
    }

    void ShaderProgramOpenGL::SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat)
    {
        GLuint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());
        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniformMatrix4fv(location, 1, GL_FALSE, mat.data());
    }
}