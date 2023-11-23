#include "VertexArray.h"

#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Buffer/VertexArrayOpenGL.h"

namespace Renderer
{

    VertexArray* VertexArray::Create()
    {
        switch (Application::GetInstance()->GetRenderApi())
        {
            case RendererApi::OpenGL:
                return new VertexArrayOpenGL();
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