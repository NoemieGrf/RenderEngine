#include "RenderCommand.h"
#include "RendererHardwareInterface/OpenGL/RenderCommand/RenderCommandOpenGL.h"

namespace Renderer
{

    RenderCommand* RenderCommand::Create(RendererApi api)
    {
        switch (api)
        {
            case RendererApi::OpenGL:
                return new RenderCommandOpenGL();
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