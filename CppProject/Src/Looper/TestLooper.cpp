#include "TestLooper.h"
#include "Input/Keyboard.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/RenderCommand/RenderCommand.h"
#include "Scene/Primitive/PrimitiveObject.h"
#include "Scene/Component/CompCamera.h"
#include "imgui.h"

using namespace Renderer;

TestLooper::TestLooper()
{
    _scene.SetRendererPipeline(RendererPipelineType::Forward);
    _scene.AddObject(PrimitiveObject::CreateQuad());

    auto pCamObj = std::make_shared<SceneObject>();
    pCamObj->AddComponent<CompCamera>(-1, 1, -1, 1, -1, 1);
    _scene.AddObject(pCamObj);
    _scene.SetMainCamera(pCamObj);
}

void TestLooper::RenderLoop()
{
    // Input
    if (Input::Keyboard::IsKeyDown(Input::KeyCode::A))
    {
        auto cam = _scene.GetMainCamera();
        auto pos = _orthoCamera.GetPosition();
        pos.x() += 0.1f;
        _orthoCamera.SetPosition(pos);
    }

    // General uniform
    _pQuadMat->GetShader()->SetUniformMat4("u_VPMatrix", _orthoCamera.GetVPMatrix());

    // Draw Call
    Renderer::RenderCommand::Submit(_quad.GetInputAssemble(), _pQuadMat);
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
