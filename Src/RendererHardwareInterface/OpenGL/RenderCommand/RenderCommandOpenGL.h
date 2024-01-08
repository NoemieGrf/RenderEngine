#pragma once

#include "Renderer/RenderCommand/RenderCommandImpl.h"

namespace Renderer
{
    class RenderCommandOpenGL : public RenderCommandImpl
    {
    public:
        RenderCommandOpenGL();
        ~RenderCommandOpenGL() override = default;

    public:
        bool SetUp() override;
        void Destroy() override;
        void SwapBuffer() override;
        void ClearColor(const Eigen::Vector4f&) override;
        void Submit(RendererPassType pass, const Ptr<InputAssemble>& pInputAssemble, const Ptr<Material>& pMaterial) override;

    public:
        const void* GetDeviceContextHandle() const;
        const void* GetRenderCoontextHandle() const;

    private:
        void* _hDeviceConext;
        void* _hRenderContext;

    };
}

