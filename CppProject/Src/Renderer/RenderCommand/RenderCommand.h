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
        static void Submit(const Ptr<InputAssemble>& pVertArray, const Ptr<Material>& pMaterial);

    private:
        inline static RenderCommandImpl* _pImpl = nullptr;
    };
}