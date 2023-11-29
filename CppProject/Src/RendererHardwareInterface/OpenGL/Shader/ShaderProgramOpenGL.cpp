#include "ShaderProgramOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
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

    bool ShaderProgramOpenGL::Link()
    {
        glLinkProgram(_shaderProgramId);
        GLint success = false;
        glGetProgramiv(_shaderProgramId, GL_LINK_STATUS, &success);
        return success;
    }

    void ShaderProgramOpenGL::Bind()
    {
        ::glUseProgram(_shaderProgramId);
    }

    void ShaderProgramOpenGL::SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat)
    {
        GLuint location = ::glGetUniformLocation(_shaderProgramId, name.c_str());

        assert(location != GL_INVALID_VALUE && location != GL_INVALID_OPERATION);

        ::glUniformMatrix4fv(location, 1, GL_FALSE, mat.data());
    }
}