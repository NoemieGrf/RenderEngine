#include "VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Helper/OpenGLHelper.h"

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
        return OpenGLHelper::CompileShader(_shaderId);
    }

    unsigned int VertexShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}