#pragma once

#include "Define/Define.h"

namespace Renderer
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

    public:
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

    public:
        static Ptr<VertexBuffer> Create(const float* vertices, unsigned int length);
    };
}
