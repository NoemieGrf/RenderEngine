#include "RendererPipeline.h"
#include "Pass/RendererPassForward.h"

namespace Renderer
{

    void RendererPipeline::Renderer(const Scene* pScene)
    {
        for (const auto& pPass : _passes)
            pPass->Renderer(pScene);
    }

    Ptr<RendererPipeline> RendererPipeline::CreateRendererPipeline(RendererPipelineType type)
    {
        Ptr<RendererPipeline> pPipe = std::make_shared<RendererPipeline>();

        switch (type)
        {
            case RendererPipelineType::Forward:
            {
                pPipe->AddPass<RendererPassForward>();
                break;
            }
            case RendererPipelineType::Deferred:
            case RendererPipelineType::ForwardPlus:
                break;
        }

        return pPipe;
    }
}