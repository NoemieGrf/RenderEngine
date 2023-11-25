#include "VertexShader.h"
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"

namespace Renderer
{

    Ptr<VertexShader> VertexShader::Create()
    {
        switch (Application::GetInstance()->GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<VertexShaderOpenGL>();
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