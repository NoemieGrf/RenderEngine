#include "PixelShader.h"
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"

namespace Renderer
{

    Ptr<PixelShader> PixelShader::Create()
    {
        switch (Application::GetInstance()->GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<PixelShaderOpenGL>();
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }

    ShaderType PixelShader::GetShaderType()
    {
        return ShaderType::Pixel;
    }
}