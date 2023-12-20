#pragma once

#include "ShaderType.h"
#include "Renderer/Assets/AssetsPool.hpp"

namespace Renderer
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

    public:
        virtual bool Compile() = 0;
        virtual ShaderType GetShaderType() = 0;
        void Load(const std::string& path);

    protected:
        virtual void LoadFromBinaray(const char* data, int size) = 0;
    };
}