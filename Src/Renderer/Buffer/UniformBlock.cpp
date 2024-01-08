#include "UniformBlock.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Buffer/UniformBlockOpenGL.h"

namespace Renderer
{
    Ptr<UniformBlock> UniformBlock::Create(const std::string& name)
    {
        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<UniformBlockOpenGL>(name);
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }

    UniformBlock::UniformBlock(const std::string& name)
        : _name(name)
    {
    }

    void UniformBlock::Set(const std::initializer_list<Element>& elements)
    {
        _uniformData = elements;
        UpdateOffset();
    }
}
