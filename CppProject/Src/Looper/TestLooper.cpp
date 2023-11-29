#include "TestLooper.h"

#include "Input/Keyboard.h"

#include "Renderer/Buffer/BufferLayout.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Shader/ShaderPool.hpp"
#include "Renderer/Shader/ShaderProgram.h"

#include "Renderer/RenderCommand/RenderCommand.h"

#include "imgui.h"

using namespace Renderer;

static constexpr const char* pvsCode = R"(
            #version 420 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec4 a_Color;

            uniform mat4 u_vpMatrix;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_vpMatrix * vec4(a_Position, 1.0);
            }
)";

static constexpr const char* pfsCode = R"(
            #version 420 core

            layout (location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
)";

static constexpr std::array<float, 3 * (3 + 4)> Vert =  {
        // left
        -0.5f, -0.5f, 0.0f, 0.2f, 0.5f, 1.7f, 1.0f,
        // right
        0.5f, -0.5f, 0.0f, 0.1f, 0.6f, 0.3f, 1.0f,
        // top
        0.0f, 0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f
};

static constexpr std::array<unsigned int, 3> Indeices = { 0, 1, 2 };

TestLooper::TestLooper()
    : _orthoCamera(-1, 1, -1, 1, -1, 1)
    , _pShader(ShaderProgram::Create())
    , _pVertexArray(VertexArray::Create())
{
    _orthoCamera.SetPosition(Eigen::Vector3f(0, 0, 0));
    _orthoCamera.SetRotation(Eigen::Quaternionf::Identity());

    _pShader->AddVertexShader(pvsCode);
    _pShader->AddPixelShader(pfsCode);
    _pShader->Link();

    Ptr<VertexBuffer> pVertexBuffer = VertexBuffer::Create(Vert.data(), Vert.size());

    // Layout
    BufferLayout layout = {
            BufferElement {ShaderDataType::Float3, "a_Position"},
            BufferElement {ShaderDataType::Float4, "a_Color"},
            //BufferElement {ShaderDataType::Float3, "a_Normal"},
    };

    pVertexBuffer->SetLayout(std::move(layout));

    // Index Buffer
    Ptr<IndexBuffer> pIndexBuffer = IndexBuffer::Create(Indeices.data(), Indeices.size());

    // Vertex Array
    _pVertexArray->AddVertexBuffer(pVertexBuffer);
    _pVertexArray->SetIndexBuffer(pIndexBuffer);
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

    // Shader Uniform
    _pShader->Bind();
    _pShader->SetUniformMat4("u_vpMatrix", _orthoCamera.GetVPMatrix());

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
