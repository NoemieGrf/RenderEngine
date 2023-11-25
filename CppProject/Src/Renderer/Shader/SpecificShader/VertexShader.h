#pragma once

#include "Define/Define.h"

namespace Renderer
{
    class VertexShader
    {
    public:
        virtual ~VertexShader() = default;

    public:
        virtual bool Compile() = 0;
        virtual void LoadFromString(const char* data) = 0;

    public:
        static Ptr<VertexShader> Create();
    };
}