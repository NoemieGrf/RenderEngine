#pragma once

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
    };

    template<ShaderType t>
    class TypeShader: public Shader
    {
    public:
        ShaderType GetType()
        {
            return t;
        }
    };
}