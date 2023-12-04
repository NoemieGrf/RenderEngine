#include "TestLooper.h"
#include "TestLooperData.h"

#include "Input/Keyboard.h"

#include "Renderer/Buffer/BufferLayout.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Assets/Image.h"
#include "Renderer/RenderCommand/RenderCommand.h"

#include "imgui.h"

using namespace Renderer;

TestLooper::TestLooper()
    : _orthoCamera(-1, 1, -1, 1, -1, 1)
    , _pTriangleShader(ShaderProgram::Create())
    , _pTriangleVertexArray(VertexArray::Create())
    , _pTriangleTexture(Texture2d::Create())
    , _pTriangleTexture2(Texture2d::Create())
{
    _orthoCamera.SetPosition(Eigen::Vector3f(0, 0, 0));
    _orthoCamera.SetRotation(Eigen::Quaternionf::Identity());

    _pTriangleShader->AddShader<ShaderType::Vertex>("Assets/Shader/BaseVertexShader.vert");
    _pTriangleShader->AddShader<ShaderType::Pixel>("Assets/Shader/BasePixelShader.frag");
    _pTriangleShader->Compile();

    Ptr<VertexBuffer> pVertexBuffer = VertexBuffer::Create(TriangleVert.data(), TriangleVert.size());

    // Layout
    BufferLayout layout = {
            BufferElement {ShaderDataType::Float3, "a_Position"},
            BufferElement {ShaderDataType::Float4, "a_Color"},
            BufferElement {ShaderDataType::Float2, "a_TexCoord"},
    };

    pVertexBuffer->SetLayout(std::move(layout));

    // Index Buffer
    Ptr<IndexBuffer> pIndexBuffer = IndexBuffer::Create(TriangleIndices.data(), TriangleIndices.size());

    // Vertex Array
    _pTriangleVertexArray->AddVertexBuffer(pVertexBuffer);
    _pTriangleVertexArray->SetIndexBuffer(pIndexBuffer);

    // Texture
    {
        Ptr<Image> pImage = std::make_shared<Image>("Assets/Texture/face.png");
        _pTriangleTexture->PushData(pImage);
    }

    {
        Ptr<Image> pImage = std::make_shared<Image>("Assets/Texture/wall.jpg");
        _pTriangleTexture2->PushData(pImage);
    }
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

    // Texture
    _pTriangleTexture->Bind(0);
    _pTriangleTexture2->Bind(1);

    // Shader Uniform
    _pTriangleShader->Bind();
    _pTriangleShader->SetUniformInt("u_Tex", 0);
    _pTriangleShader->SetUniformInt("u_Tex2", 1);
    _pTriangleShader->SetUniformMat4("u_VPMatrix", _orthoCamera.GetVPMatrix());

    // Draw Call
    Renderer::RenderCommand::Submit(_pTriangleVertexArray);
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
