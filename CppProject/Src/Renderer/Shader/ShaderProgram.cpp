#include "ShaderProgram.h"
#include "Define/RendererApi.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Shader/ShaderProgramOpenGL.h"

namespace Renderer
{
    ShaderProgram::ShaderProgram()
    {
        std::fill(_shaderArray.begin(), _shaderArray.end(), nullptr);
    }

    Ptr<ShaderProgram> ShaderProgram::Create()
    {
        switch (Application::GetRenderApi())
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

}