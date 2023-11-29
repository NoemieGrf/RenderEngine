#include "IndexBuffer.h"
#include "Application/Application.h"
#include "Define/RendererApi.h"
#include "RendererHardwareInterface/OpenGL/Buffer/IndexBufferOpenGL.h"

namespace Renderer
{
    Ptr<IndexBuffer> IndexBuffer::Create(const unsigned int* indices, unsigned int length)
    {
        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<IndexBufferOpenGL>(indices, length);
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }
}