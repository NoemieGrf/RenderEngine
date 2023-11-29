#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderType.h"
#include "Renderer/Shader/Shader.h"

namespace Renderer
{
    class PixelShader: public TypeShader<ShaderType::PixelShader>
    {
    public:
        ~PixelShader() override = default;

    public:
        static Ptr<PixelShader> Create();
    };
}