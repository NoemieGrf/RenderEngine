#pragma once

#include "Define/Define.h"
#include "Renderer/Pipeline/RendererPipelineType.h"
#include "Renderer/Pipeline/RendererPipeline.h"
#include "SceneObject.h"
#include "Component/CompCamera.h"

class Scene
{
public:
    void SetRendererPipeline(Renderer::RendererPipelineType type);
    void AddObject(const Ptr<SceneObject>& pObj);
    void Render();

    void SetMainCamera(Ptr<SceneObject>& pObj);
    const Ptr<SceneObject>& GetMainCamera() const;

    const std::vector<Ptr<SceneObject>>& GetAllObjects() const;
    const const Ptr<SceneObject>& FindFirstObjectByName(const std::string& name) const;

private:
    std::vector<Ptr<SceneObject>> _sceneObjects;
    Ptr<SceneObject> _pMainCamera = nullptr;

    Ptr<Renderer::RendererPipeline> _pRendererPipeline = nullptr;
};