#pragma once

#include "Renderer/Buffer/VertexArray.h"

namespace Renderer
{
    class VertexArrayOpenGL : public VertexArray
    {
    public:
        VertexArrayOpenGL();
        ~VertexArrayOpenGL() override;

    public:
        void Bind() override;
        void UnBind() override;
        void AddVertexBuffer(const Ptr<const VertexBuffer>& pVertexBuffer) override;
        void SetIndexBuffer(const Ptr<const IndexBuffer>& pIndexBuffer) override;
        const std::vector<Ptr<const VertexBuffer>>& GetVertexBufferVector() const override;
        Ptr<const IndexBuffer> GetCurrentIndexBuffer() const override;

    private:
        unsigned int _vertexArrayId = 0;
        std::vector<Ptr<const VertexBuffer>> _vertexBufferVec = {};
        Ptr<const IndexBuffer> _pCurrentIndexBuffer = nullptr;
    };
}