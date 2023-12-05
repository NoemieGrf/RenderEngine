#pragma once

#include "Define/Define.h"
#include "RenderCommandImpl.h"

namespace Renderer
{
    class RenderCommand
    {
    public:
        RenderCommand() = delete;
        ~RenderCommand() = delete;
        RenderCommand& operator= (const RenderCommand&) = delete;

    public:
        static void Init();
        static void Destroy();

    public:
        static void SwapBuffer();
        static void ClearColor(const Eigen::Vector4f& color);

        template<RendererPassType pass>
        static void Submit(const Ptr<InputAssemble>& pInputAssemble, const Ptr<Material>& pMaterial)
        {
            _pImpl->Submit(pass, pInputAssemble, pMaterial);
        }

    private:
        inline static RenderCommandImpl* _pImpl = nullptr;
    };
}