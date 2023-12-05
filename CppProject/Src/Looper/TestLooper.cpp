#include "TestLooper.h"
#include "TestLooperData.h"

#include "Input/Keyboard.h"

#include "Renderer/Buffer/InputLayout.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Assets/Image.h"
#include "Renderer/RenderCommand/RenderCommand.h"

#include "imgui.h"

using namespace Renderer;

TestLooper::TestLooper()
    : _orthoCamera(-1, 1, -1, 1, -1, 1)
{
    _orthoCamera.SetPosition(Eigen::Vector3f(0, 0, 0));
    _orthoCamera.SetRotation(Eigen::Quaternionf::Identity());

    PrepareTriangle();
    PrepareBox();
}

void TestLooper::PrepareTriangle()
{
    _pTriangleInputAssemble = InputAssemble::Create();

    // Layout
    _pTriangleInputAssemble->SetInputLayout({
        InputLayoutElement {ShaderDataType::Float3, "a_Position"},
        InputLayoutElement {ShaderDataType::Float4, "a_Color"},
        InputLayoutElement {ShaderDataType::Float2, "a_TexCoord"},
        });

    // Vertex Array
    Ptr<VertexBuffer> pVertexBuffer = VertexBuffer::Create(TriangleVert.data(), TriangleVert.size());
    _pTriangleInputAssemble->SetVertexBuffer(pVertexBuffer);

    // Index Buffer
    Ptr<IndexBuffer> pIndexBuffer = IndexBuffer::Create(TriangleIndices.data(), TriangleIndices.size());
    _pTriangleInputAssemble->SetIndexBuffer(pIndexBuffer);

    // Mat
    _pTriangleMaterial = std::make_shared<Material>("Assets/Material/TriangleMat.json");
}

void TestLooper::PrepareBox()
{
    // todo
}

void TestLooper::RenderLoop()
{
    // Input
    if (Input::Keyboard::IsKeyDown(Input::KeyCode::A))
    {
        auto pos = _orthoCamera.GetPosition();
        pos.x() += 0.1f;
        _orthoCamera.SetPosition(pos);
    }

    // General uniform
    _pTriangleMaterial->GetShader()->SetUniformMat4("u_VPMatrix", _orthoCamera.GetVPMatrix());

    // Draw Call
    Renderer::RenderCommand::Submit(_pTriangleInputAssemble, _pTriangleMaterial);
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
