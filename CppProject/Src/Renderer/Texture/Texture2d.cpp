#include <memory>

#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Texture/Texture2dOpenGL.h"
#include "Texture2d.h"


namespace Renderer 
{
    Ptr<Texture2d> Texture2d::Create()
    {
        auto api = Application::GetRenderApi();
        switch (api) 
        {
            case RendererApi::OpenGL:
                return std::make_shared<Texture2dOpenGL>();
            case RendererApi::Vulkan:
            case RendererApi::D3D11:
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }
}