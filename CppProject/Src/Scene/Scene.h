#pragma once

#include "Define/Define.h"
#include "Renderer/Pipeline/RendererPipeline.h"
#include "Renderer/Pipeline/RendererPipelineType.h"

class Scene
{
public:
    void SetRendererPipeline(Renderer::RendererPipelineType type);

private:
    Ptr<Renderer::RendererPipeline> _pRendererPipeline = nullptr;
};