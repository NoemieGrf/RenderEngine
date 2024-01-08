#pragma once

#include "Define/Define.h"
#include "UniformBlock.h"

namespace Renderer
{
    class UniformBuffer
    {
    public:
        virtual ~UniformBuffer() = default;

    public:
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

    public:
        static Ptr<UniformBuffer> Create();

    private:
        Ptr<UniformBlock> _pUniformBlock;
    };
}