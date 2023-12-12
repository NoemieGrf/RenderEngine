#include "PrimitiveObject.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Assets/AssetsPool.hpp"
#include "Renderer/Assets/Model.h"

static constexpr std::array<float, 4 * (3 + 2)> QuadVert =  {
        /* left bottom */  -0.5f, -0.5f, 0.0f, /* UV */ 0.0f, 0.0f,
        /* right bottom */  0.5f, -0.5f, 0.0f, /* UV */ 1.0f, 0.0f,
        /* right top */     0.5f,  0.5f, 0.0f, /* UV */ 1.0f, 1.0f,
        /* left top */     -0.5f,  0.5f, 0.0f, /* UV */ 0.0f, 1.0f
};

static constexpr std::array<unsigned int, 6> QuadIndices = {0, 1, 2, 0, 2, 3 };

static Renderer::InputLayout QuadVertLayout = {
        Renderer::InputLayoutElement {Renderer::ShaderDataType::Float3, "a_Position"},
        Renderer::InputLayoutElement {Renderer::ShaderDataType::Float2, "a_TexCoord"},
};

Ptr<SceneObject> PrimitiveObject::CreateQuad()
{
    Ptr<SceneObject> pObj = std::make_shared<SceneObject>();

    auto pInputAssemble = Renderer::InputAssemble::Create();
    pInputAssemble->SetInputLayout(QuadVertLayout);
    pInputAssemble->SetVertexBuffer(QuadVert.data(), QuadVert.size());
    pInputAssemble->SetIndexBuffer(QuadIndices.data(), QuadIndices.size());

    auto pDefaultMaterial = std::make_shared<Renderer::Material>("Assets/Material/DefaultMaterial.json");

    pObj->AddComponent<CompRenderer>(pInputAssemble, pDefaultMaterial);

    return pObj;
}

Ptr<SceneObject> PrimitiveObject::CreateBox()
{
    auto pModel = Renderer::AssetsPool<Renderer::Model>::Get("Assets/Model/Cube.obj");
    auto allMesh = pModel->GetMeshMap();
}
