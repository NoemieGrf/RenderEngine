#pragma once

#include "Define/Define.h"
#include "Renderer/Pipeline/RendererPipelineType.h"

namespace Renderer
{
    class RendererPipeline;
}

class Scene
{
public:
    void SetRendererPipeline(Renderer::RendererPipelineType type);

private:
    Ptr<Renderer::RendererPipeline> _pRendererPipeline = nullptr;
};