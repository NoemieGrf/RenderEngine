#pragma once

#include "Define/Define.h"
#include "Util/NonCopyable.h"
#include "Define/RendererApi.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Material/Material.h"
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
        virtual void Submit(const Ptr<VertexArray>& pVertArray, const Ptr<Material>& pMaterial) = 0;
    };
}