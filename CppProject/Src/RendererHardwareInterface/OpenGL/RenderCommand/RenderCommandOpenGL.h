#pragma once

#include "Renderer/RenderCommand/RenderCommandImpl.h"

namespace Renderer
{
    struct RhiOpenGLData;

    class RenderCommandOpenGL : public RenderCommandImpl
    {
    public:
        RenderCommandOpenGL();
        ~RenderCommandOpenGL() override;

    public:
        bool SetUp() override;
        void Destroy() override;
        void SwapBuffer() override;
        void ClearColor(const Eigen::Vector4f&) override;
        void Submit(const Ptr<VertexArray>& pVertArray) override;

    public:
        const RhiOpenGLData* GetData() const;

    private:
        RhiOpenGLData* _pData;

    };
}

