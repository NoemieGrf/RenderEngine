#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/Shader.h"

namespace Renderer
{
    class PixelShader: public Shader
    {
    public:
        ~PixelShader() override = default;
        ShaderType GetShaderType() override;

    public:
        static Ptr<PixelShader> Create();
    };
}