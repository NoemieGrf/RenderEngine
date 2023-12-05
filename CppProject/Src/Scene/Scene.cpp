#include "Scene.h"

void Scene::SetRendererPipeline(Renderer::RendererPipelineType type)
{
    _pRendererPipeline = Renderer::RendererPipeline::CreateRendererPipeline(type);
}
