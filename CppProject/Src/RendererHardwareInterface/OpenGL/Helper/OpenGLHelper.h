#pragma once

#include <string>
#include <eigen/Eigen>
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    class OpenGLHelper
    {
    public:
        OpenGLHelper() = delete;
        ~OpenGLHelper() = delete;
        OpenGLHelper& operator= (const OpenGLHelper&) = delete;

    public:
        static GLenum GetShaderDataTypeGlEnum(ShaderDataType type);
        static bool CompileShader(unsigned int shaderId);
    };
}