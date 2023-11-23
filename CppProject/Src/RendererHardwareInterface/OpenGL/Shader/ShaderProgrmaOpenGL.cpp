#include "ShaderProgrmaOpenGL.h"
#include "VertexShaderOpenGL.h"
#include "PixelShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    ShaderProgramOpenGL::ShaderProgramOpenGL()
    {
        _shaderProgramId = ::glCreateProgram();
    }

    void ShaderProgramOpenGL::AddVertexShader(VertexShader* pVertexShader)
    {
        auto pVSOpenGL = dynamic_cast<const VertexShaderOpenGL*>(pVertexShader);
        if (pVSOpenGL == nullptr)
            return;

        ::glAttachShader(_shaderProgramId, pVSOpenGL->GetShaderId());
    }

    void ShaderProgramOpenGL::AddPixelShader(PixelShader* pPixelShader)
    {
        auto pPSOpenGL = dynamic_cast<const PixelShaderOpenGL*>(pPixelShader);
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