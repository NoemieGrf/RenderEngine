#include "TestLooper.h"

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

static constexpr std::array<float, 4 * (3 + 4 + 2)> Vert =  {
        /* left bottom */  -0.5f, -0.5f, 0.0f,
        /* Color */ 0.2f, 0.5f, 1.7f, 1.0f,
        /* UV */ 0.0f, 0.0f,
        /* right bottom */  0.5f, -0.5f, 0.0f,
        /* Color */ 0.1f, 0.6f, 0.3f, 1.0f,
        /* UV */ 1.0f, 0.0f,
        /* right top */     0.5f, 0.5f, 0.0f,
        /* Color */ 0.8f, 0.2f, 0.1f, 1.0f,
        /* UV */ 1.0f, 1.0f,
        /* left top */     -0.5f, 0.5f, 0.0f,
        /* Color */ 0.8f, 0.2f, 0.1f, 1.0f,
        /* UV */ 0.0f, 1.0f
};

static constexpr std::array<unsigned int, 6> Indeices = { 0, 1, 2, 0, 2,3 };

TestLooper::TestLooper()
    : _orthoCamera(-1, 1, -1, 1, -1, 1)
    , _pShader(ShaderProgram::Create())
    , _pVertexArray(VertexArray::Create())
    , _pTexture(Texture2d::Create())
{
    _orthoCamera.SetPosition(Eigen::Vector3f(0, 0, 0));
    _orthoCamera.SetRotation(Eigen::Quaternionf::Identity());

    _pShader->AddShader<ShaderType::Vertex>("Assets/Shader/BaseVertexShader.vert");
    _pShader->AddShader<ShaderType::Pixel>("Assets/Shader/BasePixelShader.frag");
    _pShader->Compile();

    Ptr<VertexBuffer> pVertexBuffer = VertexBuffer::Create(Vert.data(), Vert.size());

    // Layout
    BufferLayout layout = {
            BufferElement {ShaderDataType::Float3, "a_Position"},
            BufferElement {ShaderDataType::Float4, "a_Color"},
            BufferElement {ShaderDataType::Float2, "a_TexCoord"},
    };

    pVertexBuffer->SetLayout(std::move(layout));

    // Index Buffer
    Ptr<IndexBuffer> pIndexBuffer = IndexBuffer::Create(Indeices.data(), Indeices.size());

    // Vertex Array
    _pVertexArray->AddVertexBuffer(pVertexBuffer);
    _pVertexArray->SetIndexBuffer(pIndexBuffer);

    // Texture
    Ptr<Image> pImage = std::make_shared<Image>("Assets/Texture/face.png");
    _pTexture->PushData(pImage);
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
    _pTexture->Bind(0);

    // Shader Uniform
    _pShader->Bind();
    _pShader->SetUniformInt("u_Tex", 0);
    _pShader->SetUniformMat4("u_VPMatrix", _orthoCamera.GetVPMatrix());

    // Draw Call
    Renderer::RenderCommand::Submit(_pVertexArray);
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
