#include "TestLooper.h"
#include "Input/Keyboard.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Scene/Primitive/PrimitiveObject.h"
#include "Scene/Component/CompCamera.h"
#include "Scene/Component/CompRenderer.h"
#include "Math/Math.h"
#include "imgui.h"

using namespace Renderer;

TestLooper::TestLooper()
{
    _scene.SetRendererPipeline(RendererPipelineType::Forward);

    auto pQuadObj = PrimitiveObject::CreateQuad();
    pQuadObj->GetComponent<CompRenderer>()->ChangeMaterial(std::make_shared<Material>("Assets/Material/TextureMixtureMat.json"));
    pQuadObj->SetPosition({0, 0, -10});
    pQuadObj->SetScale({0.7f, 0.7f, 1.0f});
    _scene.AddObject(pQuadObj);

    auto pCamObj = std::make_shared<SceneObject>();
    pCamObj->AddComponent<CompCamera>(Eigen::Vector2f{1, 1}, -20, -100);
    pCamObj->SetPosition({0, 0, 25});

    _scene.AddObject(pCamObj);
    _scene.SetMainCamera(pCamObj);
}

void TestLooper::RenderLoop()
{
    // Input
    if (Input::Keyboard::IsKeyDown(Input::KeyCode::A))
    {
        auto pCamObj = _scene.GetMainCamera();
        auto pos = pCamObj->GetLocalPosition();
        pos.x() += 0.001f;
        pCamObj->SetPosition(pos);
    }

    _scene.Render();
}

void TestLooper::EditorLoop()
{
    // temp
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(main_viewport->WorkPos.x / 3, main_viewport->WorkPos.y / 2), ImGuiCond_Always);

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Test", nullptr, window_flags);

    ImGui::Button("Test");

    ImGui::End();
}
