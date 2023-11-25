#pragma once

#include "Define/Define.h"

namespace Renderer
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

    public:
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        virtual unsigned int GetIndicesCount() const = 0;

    public:
        static Ptr<IndexBuffer> Create(const unsigned int* indices, unsigned int length);
    };
}