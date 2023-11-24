#pragma once

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
        static void Submit(VertexArray* pVertArray);

    private:
        inline static RenderCommandImpl* _pImpl = nullptr;
    };
}