#pragma once

#include "Shader.h"

namespace Renderer
{
    class PixelShader: public Shader
    {
    public:
        static PixelShader* Create();
    };
}