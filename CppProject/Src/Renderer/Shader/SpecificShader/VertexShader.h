#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderType.h"
#include "Renderer/Shader/Shader.h"

namespace Renderer
{
    class VertexShader: public TypeShader<ShaderType::VertexShader>
    {
    public:
        ~VertexShader() override = default;

    public:
        static Ptr<VertexShader> Create();
    };
}