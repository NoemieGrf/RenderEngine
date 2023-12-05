#include "Scene.h"
#include "Renderer/Pipeline/RendererPipeline.h"

void Scene::SetRendererPipeline(Renderer::RendererPipelineType type)
{
    _pRendererPipeline = Renderer::RendererPipeline::CreateRendererPipeline(type);
}
