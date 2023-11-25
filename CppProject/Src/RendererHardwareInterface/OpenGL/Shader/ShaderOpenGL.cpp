#include "ShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"

namespace Renderer
{

    ShaderProgramOpenGL::ShaderProgramOpenGL()
    {
        _shaderProgramId = ::glCreateProgram();
    }

    void ShaderProgramOpenGL::AttachVertexShader()
    {
        Ptr<VertexShaderOpenGL> pVSOpenGL = DynamicCast<VertexShaderOpenGL>(_pVertexShader);
        if (pVSOpenGL == nullptr)
            return;

        ::glAttachShader(_shaderProgramId, pVSOpenGL->GetShaderId());
    }

    void ShaderProgramOpenGL::AttachPixelShader()
    {
        Ptr<PixelShaderOpenGL> pPSOpenGL = DynamicCast<PixelShaderOpenGL>(_pPixelShader);
        if (pPSOpenGL == nullptr)
            return;

        ::glAttachShader(_shaderProgramId, pPSOpenGL->GetShaderId());
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