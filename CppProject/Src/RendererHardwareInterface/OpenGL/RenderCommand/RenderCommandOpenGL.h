#pragma once

#include "Renderer/RenderCommand/RenderCommand.h"

namespace Renderer
{
    struct RhiOpenGLData;

    class RenderCommandOpenGL : public RenderCommand
    {
    public:
        RenderCommandOpenGL();
        ~RenderCommandOpenGL() override;

    public:
        bool SetUp() override;
        void Destroy() override;
        void SwapBuffer() override;
        void ClearColor(Eigen::Vector4f color) override;
        void Submit(VertexArray* pVertArray) override;

    public:
        const RhiOpenGLData* GetData() const;

    private:
        RhiOpenGLData* _pData;

    };
}

