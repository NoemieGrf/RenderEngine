#include "RenderLooper.h"

#include "Application/Application.h"
#include "Renderer/Buffer/BufferLayout.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Shader/SpecificShader/VertexShader.h"
#include "Renderer/Shader/SpecificShader/PixelShader.h"
#include "Renderer/Camera/OrthoCamera.h"
#include "Renderer/RenderCommand/RenderCommand.h"

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

void RenderLooper::Loop()
{
    OrthoCamera camera(-1, 1, -1, 1, -1, 1);

    Ptr<Shader> pShader = Shader::Create();
    pShader->AddVertexShader(pvsCode);
    pShader->AddPixelShader(pfsCode);
    pShader->Link();

    VertexBuffer* pVertexBuffer = VertexBuffer::Create(Vert.data(), Vert.size());

    // Layout
    BufferLayout layout = {
            BufferElement {ShaderDataType::Float3, "a_Position"},
            BufferElement {ShaderDataType::Float4, "a_Color"},
            //BufferElement {ShaderDataType::Float3, "a_Normal"},
    };

    pVertexBuffer->SetLayout(std::move(layout));

    // Index Buffer
    IndexBuffer* pIndexBuffer = IndexBuffer::Create(Indeices.data(), Indeices.size());

    // Vertex Array
    VertexArray* pVertexArray = VertexArray::Create();
    pVertexArray->AddVertexBuffer(pVertexBuffer);
    pVertexArray->SetIndexBuffer(pIndexBuffer);

    // Shader Uniform
    pShader->Bind();
    pShader->SetUniformMat4("u_vpMatrix", camera.GetVPMatrix());

    // Draw Call
    Renderer::RenderCommand::Submit(pVertexArray);

    // Clear
    delete pVertexArray;
    delete pIndexBuffer;
    delete pVertexBuffer;
}

