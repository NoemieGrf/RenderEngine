#include "Shader.h"
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Shader/ShaderOpenGL.h"

namespace Renderer
{

    Ptr<Shader> Shader::Create()
    {
        switch (Application::GetInstance()->GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<ShaderProgramOpenGL>();
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }

    void Shader::AddVertexShader(const char* vertexShaderSource)
    {
        _pVertexShader = VertexShader::Create();
        _pVertexShader->LoadFromString(vertexShaderSource);
        _pVertexShader->Compile();
        AttachVertexShader();
    }

    void Shader::AddPixelShader(const char* pixelShaderSource)
    {
        _pPixelShader = PixelShader::Create();
        _pPixelShader->LoadFromString(pixelShaderSource);
        _pPixelShader->Compile();
        AttachPixelShader();
    }
}