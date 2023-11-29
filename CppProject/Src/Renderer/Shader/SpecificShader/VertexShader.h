#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderType.h"
#include "Renderer/Shader/Shader.h"

namespace Renderer
{
    class VertexShader: public Shader
    {
    public:
        ~VertexShader() override = default;
        ShaderType GetShaderType() override;

    public:
        static Ptr<VertexShader> Create();
    };
}