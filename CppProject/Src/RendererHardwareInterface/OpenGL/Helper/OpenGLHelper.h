#pragma once

#include <string>
#include <eigen/Eigen>
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "Renderer/Shader/ShaderDataType.h"
#include "Util/NonConstructible.h"

namespace Renderer
{
    class OpenGLHelper: public NonConstructible
    {
    public:
        static GLenum GetShaderDataTypeGlEnum(ShaderDataType type);
        static bool CompileShader(unsigned int shaderId);
        static std::string GetShaderInfoLog(unsigned int shaderId);
        static std::string GetProgramInfoLog(unsigned int programId);

    private:
        static void CheckInfoBuffer();

    private:
        inline static constexpr int GL_INFO_BUFFER_SIZE = 512;
        inline static char* _pInfoLogBuffer = nullptr;
    };
}