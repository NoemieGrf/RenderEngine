#include "Application/Application.h"
#include "RenderCommand.h"
#include "RendererHardwareInterface/OpenGL/RenderCommand/RenderCommandOpenGL.h"

namespace Renderer
{
    void Renderer::RenderCommand::Init()
    {
        auto api = Application::GetRenderApi();
        switch (api)
        {
            case RendererApi::OpenGL:
                _pImpl = new RenderCommandOpenGL();
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        assert(_pImpl != nullptr);

        _pImpl->SetUp();
    }

    void RenderCommand::Destroy()
    {
        _pImpl->Destroy();
        delete _pImpl;
    }

    void RenderCommand::SwapBuffer()
    {
        _pImpl->SwapBuffer();
    }

    void RenderCommand::ClearColor(const Eigen::Vector4f& color)
    {
        _pImpl->ClearColor(color);
    }

    void RenderCommand::Submit(const Ptr<InputAssemble>& pVertArray, const Ptr<Material>& pMaterial)
    {
        _pImpl->Submit(pVertArray, pMaterial);
    }



}