#pragma once

#include "Renderer/Buffer/VertexBuffer.h"

namespace Renderer
{
    class VertexBufferOpenGL : public VertexBuffer
    {
    public:
        explicit VertexBufferOpenGL(const float* vertices, unsigned int length);
        ~VertexBufferOpenGL() override;

    public:
        void Bind() const override;
        void UnBind() const override;
        void SetLayout(const InputLayout& layout) override;
        void SetLayout(InputLayout&& layout) override;
        const InputLayout& GetLayout() const override;

    private:
        unsigned int _renderId = 0;
        InputLayout _bufferLayout;
    };
}