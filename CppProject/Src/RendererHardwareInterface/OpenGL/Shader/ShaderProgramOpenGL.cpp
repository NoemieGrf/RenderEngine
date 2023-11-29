#include "ShaderProgramOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    ShaderProgramOpenGL::ShaderProgramOpenGL()
    {
        _shaderProgramId = ::glCreateProgram();
    }

    void ShaderProgramOpenGL::AttachShader(ShaderType t)
    {
        auto p = GetShader<t>();
        auto itr = _shaderMap.find(t);
        if (itr == _shaderMap.end())
        {
            Util::Logger::LogWarn("Do not have {}, but trying to attach.", ShaderTypeHelper::ShaderTypeToString(t));
            return;
        }

        Ptr<IOpenGLShaderId> pOpenGLShader = DynamicCast<IOpenGLShaderId>(itr->second);
        if (pOpenGLShader == nullptr)
        {
            Util::Logger::LogWarn("Shader convert fail `{}` when attaching.", ShaderTypeHelper::ShaderTypeToString(t));
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