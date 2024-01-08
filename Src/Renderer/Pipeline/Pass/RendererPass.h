#pragma once

#include "Define/Define.h"
#include "Renderer/Buffer/UniformBlock.h"
#include "Renderer/Buffer/UniformBuffer.h"

class Scene;

namespace Renderer
{
    class RendererPass
    {
    public:
        struct PassUniform
        {
            Ptr<UniformBlock> pUniformBlock;
            Ptr<UniformBuffer> pUniformBuffer;
        };

    public:
        virtual void Init() = 0;
        virtual void Renderer(const Scene* pScene) = 0;
    };
}