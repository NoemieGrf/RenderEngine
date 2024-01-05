#pragma once

#include <string>
#include <eigen/Eigen>
#include <Helper/NonConstructible.h>
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    class OpenGLHelper: public Helper::NonConstructible
    {
    public:
        static GLenum GetShaderDataTypeGlEnum(ShaderDataType type);
        static bool CheckShaderState(unsigned int shaderId);
        static std::string GetShaderInfoLog(unsigned int shaderId);
        static std::string GetProgramInfoLog(unsigned int programId);

    private:
        static void CheckInfoBuffer();

    private:
        inline static constexpr int GL_INFO_BUFFER_SIZE = 512;
        inline static char* _pInfoLogBuffer = nullptr;
    };
}