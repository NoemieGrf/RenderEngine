#include "VertexShader.h"
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Shader/SpecificShader/VertexShaderOpenGL.h"

namespace Renderer
{

    Ptr<VertexShader> VertexShader::Create(const std::string& binPath)
    {
        Ptr<VertexShaderOpenGL> pResult = nullptr;

        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                pResult = std::make_shared<VertexShaderOpenGL>();
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

    ShaderType VertexShader::GetShaderType()
    {
        return ShaderType::Vertex;
    }
}