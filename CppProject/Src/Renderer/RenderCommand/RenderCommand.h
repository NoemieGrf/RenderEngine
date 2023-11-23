#pragma once

#include "Util/NonCopyable.h"
#include "Define/RendererApi.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "eigen/Eigen"

namespace Renderer
{
    class RenderCommand : public NonCopyable
    {
    public:
        virtual ~RenderCommand() = default;

    public:
        virtual bool SetUp() = 0;
        virtual void Destroy() = 0;
        virtual void SwapBuffer() = 0;
        virtual void ClearColor(Eigen::Vector4f color) = 0;
        virtual void Submit(VertexArray* pVertArray) = 0;

    public:
        static RenderCommand* Create(RendererApi api);
    };
}