#pragma once

#include <string>

namespace Renderer
{
    class OpenGLHelper
    {
    public:
        OpenGLHelper() = delete;

    public:
        static bool CompileShader(unsigned int shaderId);
    };
}