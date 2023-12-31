#pragma once

#include <vector>

#include "Define/Define.h"
#include "Renderer/Assets/Mesh.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"

namespace Renderer
{
    class InputAssemble
    {
    public:
        virtual ~InputAssemble() = default;

    public:
        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        void SetInputLayout(const InputLayout& layout);
        void SetVertexBuffer(const Ptr<VertexBuffer>& pVertexBuffer);
        void SetVertexBuffer(const float* vertices, unsigned int length);
        void SetIndexBuffer(const Ptr<IndexBuffer>& pIndexBuffer);
        void SetIndexBuffer(const unsigned int* indices, unsigned int length);
        const InputLayout& GetInputLayout() const;
        const Ptr<VertexBuffer>& GetVertexBuffer() const;
        const Ptr<IndexBuffer>& GetIndexBuffer() const;

    protected:
        InputLayout _inputLayout = {};
        Ptr<VertexBuffer> _pVertexBuffer;
        Ptr<IndexBuffer> _pIndexBuffer;

    public:
        static Ptr<InputAssemble> Create();
        static Ptr<InputAssemble> Create(const Ptr<Mesh>& pMesh);
    };
}