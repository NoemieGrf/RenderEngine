#include "InputAssemble.h"

#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/InputAssemble/InputAssembleOpenGL.h"

namespace Renderer
{

    Ptr<InputAssemble> InputAssemble::Create()
    {
        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<InputAssembleOpenGL>();
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }

    Ptr<InputAssemble> InputAssemble::Create(const Ptr<Mesh>& pMesh)
    {
        Ptr<InputAssemble> pInputAssemble = Create();

        const auto& vertexData = pMesh->GetVertexData();
        const auto& indexData = pMesh->GetIndexData();

        pInputAssemble->SetVertexBuffer(vertexData.data(), vertexData.size());
        pInputAssemble->SetIndexBuffer(indexData.data(), indexData.size());
        pInputAssemble->SetInputLayout(pMesh->GetLayout());

        return pInputAssemble;
    }

    void InputAssemble::SetInputLayout(const InputLayout& layout)
    {
        _inputLayout = layout;
    }

    void InputAssemble::SetVertexBuffer(const Ptr<VertexBuffer>& pVertexBuffer)
    {
        _pVertexBuffer = pVertexBuffer;
    }

    void InputAssemble::SetVertexBuffer(const float* vertices, unsigned int length)
    {
        _pVertexBuffer = VertexBuffer::Create(vertices, length);
    }

    void InputAssemble::SetIndexBuffer(const Ptr<IndexBuffer>& pIndexBuffer)
    {
        _pIndexBuffer = pIndexBuffer;
    }

    void InputAssemble::SetIndexBuffer(const unsigned int* indices, unsigned int length)
    {
        _pIndexBuffer = IndexBuffer::Create(indices, length);
    }

    const InputLayout& InputAssemble::GetInputLayout() const
    {
        return _inputLayout;
    }

    const Ptr<VertexBuffer>& InputAssemble::GetVertexBuffer() const
    {
        return _pVertexBuffer;
    }

    const Ptr<IndexBuffer>& InputAssemble::GetIndexBuffer() const
    {
        return _pIndexBuffer;
    }
}