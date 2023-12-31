#pragma once

#include "Renderer/Buffer/VertexBuffer.h"

namespace Renderer
{
    class VertexBufferOpenGL : public VertexBuffer
    {
    public:
        VertexBufferOpenGL(const float* vertices, unsigned int length);
        ~VertexBufferOpenGL() override;

    public:
        void Bind() const override;
        void UnBind() const override;

    private:
        unsigned int _renderId = 0;
    };
}