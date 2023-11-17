#pragma once

#include "Shader.h"

namespace Renderer
{
    class VertexShader: public Shader
    {
    public:
        static VertexShader* Create();
    };
}