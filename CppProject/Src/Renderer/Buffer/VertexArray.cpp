#include "VertexArray.h"

#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Buffer/VertexArrayOpenGL.h"

namespace Renderer
{

    Ptr<VertexArray> VertexArray::Create()
    {
        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<VertexArrayOpenGL>();
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