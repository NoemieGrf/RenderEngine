#include "Scene.h"
#include "Renderer/Pipeline/RendererPipeline.h"
#include "Component/CompCamera.h"

void Scene::SetRendererPipeline(Renderer::RendererPipelineType type)
{
    _pRendererPipeline = Renderer::RendererPipeline::CreateRendererPipeline(type);
}

void Scene::AddObject(const Ptr<SceneObject>& pObj)
{
    // todo: duplicate ?
    if (pObj != nullptr)
        _sceneObjects.push_back(pObj);
}

void Scene::Render()
{
    assert(_pRendererPipeline != nullptr);

    _pRendererPipeline->Renderer(this);
}

void Scene::SetMainCamera(Ptr<SceneObject>& pObj)
{
    assert(pObj != nullptr);

    auto pCompCamera = pObj->GetComponent<CompCamera>();
    assert(pCompCamera != nullptr);

    _pMainCamera = pObj;
}

const Ptr<SceneObject>& Scene::GetMainCamera() const
{
    return _pMainCamera;
}

const std::vector<Ptr<SceneObject>>& Scene::GetAllObjects() const
{
    return _sceneObjects;
}
const Ptr<SceneObject>& Scene::FindFirstObjectByName(const std::string& name) const
{
    for (const auto& pObj: _sceneObjects)
    {
        if (pObj->GetName() == name)
            return pObj;
    }

    return nullptr;
}
