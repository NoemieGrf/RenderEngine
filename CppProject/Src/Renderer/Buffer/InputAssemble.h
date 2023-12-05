#pragma once

#include <vector>

#include "Define/Define.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Renderer
{
    class InputAssemble
    {
    public:
        virtual ~InputAssemble() = default;

    public:
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void AddVertexBuffer(const Ptr<const VertexBuffer>& pVertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ptr<const IndexBuffer>& pIndexBuffer) = 0;
        virtual const std::vector<Ptr<const VertexBuffer>>& GetVertexBufferVector() const = 0;
        virtual Ptr<const IndexBuffer> GetCurrentIndexBuffer() const = 0;

    public:
        static Ptr<InputAssemble> Create();
    };
}