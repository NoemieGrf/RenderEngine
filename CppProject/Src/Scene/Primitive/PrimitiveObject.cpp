#include "PrimitiveObject.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Assets/AssetsPool.hpp"
#include "Renderer/Assets/Model.h"

Ptr<SceneObject> PrimitiveObject::CreateQuad()
{
    return LoadFromObj("Assets/Primitive/Model/Quad.obj");
}

Ptr<SceneObject> PrimitiveObject::CreateBox()
{
    return LoadFromObj("Assets/Primitive/Model/Cube.obj");
}

Ptr<SceneObject> PrimitiveObject::LoadFromObj(const std::string& path)
{
    auto pModel = Renderer::AssetsPool<Renderer::Model>::Get(path);
    auto allMesh = pModel->GetMeshMap();

    if (allMesh.empty())
        return nullptr;

    if (allMesh.size() == 1)
    {
        Ptr<SceneObject> pObj = std::make_shared<SceneObject>();

        auto pInputAssemble = Renderer::InputAssemble::Create(allMesh.begin()->second);
        auto pDefaultMaterial = std::make_shared<Renderer::Material>("Assets/Primitive/Material/DefaultMaterial.json");
        pObj->AddComponent<CompRenderer>(pInputAssemble, pDefaultMaterial);

        return pObj;
    }
    else
    {
        Ptr<SceneObject> pParentObj = std::make_shared<SceneObject>();
        for (const auto& [name, mesh]: allMesh)
        {
            Ptr<SceneObject> pObj = std::make_shared<SceneObject>();

            auto pInputAssemble = Renderer::InputAssemble::Create(allMesh.begin()->second);
            auto pDefaultMaterial = std::make_shared<Renderer::Material>("Assets/Primitive/Material/DefaultMaterial.json");
            pObj->AddComponent<CompRenderer>(pInputAssemble, pDefaultMaterial);

            pParentObj->AddChild(pObj);
        }

        return pParentObj;
    }
}
