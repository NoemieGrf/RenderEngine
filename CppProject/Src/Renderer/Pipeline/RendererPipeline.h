#pragma once

#include "Pass/RendererPass.h"
#include "RendererPipelineType.h"

namespace Renderer
{
    class RendererPipeline
    {
    public:
        void Renderer(const Scene* pScene);

    public:
        static Ptr<RendererPipeline> CreateRendererPipeline(RendererPipelineType type);

    private:
        template<typename Pass>
        void AddPass()
        {
            Ptr<Pass> pPass = std::make_shared<Pass>();
            pPass->Init();
            Ptr<RendererPass> pTopPass = DynamicCast<RendererPass>(pPass);
            _passes.push_back(pTopPass);
        }

    private:
        std::vector<Ptr<RendererPass>> _passes;
    };

}