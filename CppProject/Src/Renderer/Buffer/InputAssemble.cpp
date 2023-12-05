#include "InputAssemble.h"

#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Buffer/InputAssembleOpenGL.h"

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
}