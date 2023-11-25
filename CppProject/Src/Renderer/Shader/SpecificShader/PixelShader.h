#pragma once

#include "Define/Define.h"

namespace Renderer
{
    class PixelShader
    {
    public:
        virtual ~PixelShader() = default;

    public:
        virtual bool Compile() = 0;
        virtual void LoadFromString(const char* data) = 0;

    public:
        static Ptr<PixelShader> Create();
    };
}