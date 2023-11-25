#pragma once

#include "Util/NonCopyable.h"
#include "Define/RendererApi.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/Shader.h"
#include "eigen/Eigen"

namespace Renderer
{
    class RenderCommandImpl : public NonCopyable
    {
    public:
        virtual ~RenderCommandImpl() = default;

    public:
        virtual bool SetUp() = 0;
        virtual void Destroy() = 0;
        virtual void SwapBuffer() = 0;
        virtual void ClearColor(const Eigen::Vector4f& color) = 0;
        virtual void Submit(VertexArray* pVertArray) = 0;
    };
}