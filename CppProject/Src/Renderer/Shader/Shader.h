#pragma once

#include "ShaderType.h"
#include <concepts>

namespace Renderer
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

    public:
        virtual bool Compile() = 0;
        virtual void LoadFromString(const char* data) = 0;
        virtual ShaderType GetShaderType() = 0;

    };
}