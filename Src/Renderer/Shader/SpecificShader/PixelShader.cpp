#include "PixelShader.h"
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/PixelShaderOpenGL.h"

namespace Renderer
{

    Ptr<PixelShader> PixelShader::Create(const std::string& binPath)
    {
        Ptr<PixelShaderOpenGL> pResult = nullptr;

        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                pResult = std::make_shared<PixelShaderOpenGL>();
                break;
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        if (pResult != nullptr)
            pResult->Load(binPath);

        return pResult;
    }

    ShaderType PixelShader::GetShaderType()
    {
        return ShaderType::Pixel;
    }
}