#include "Quad.h"

static constexpr std::array<float, 4 * (3 + 2)> Vert =  {
        /* left bottom */  -0.5f, -0.5f, 0.0f, /* UV */ 0.0f, 0.0f,
        /* right bottom */  0.5f, -0.5f, 0.0f, /* UV */ 1.0f, 0.0f,
        /* right top */     0.5f,  0.5f, 0.0f, /* UV */ 1.0f, 1.0f,
        /* left top */     -0.5f,  0.5f, 0.0f, /* UV */ 0.0f, 1.0f
};

static constexpr std::array<unsigned int, 6> Indices = {0, 1, 2, 0, 2, 3 };

static Renderer::InputLayout VertLayout = {
        Renderer::InputLayoutElement {Renderer::ShaderDataType::Float3, "a_Position"},
        Renderer::InputLayoutElement {Renderer::ShaderDataType::Float2, "a_TexCoord"},
};


Quad::Quad()
{
    _pInputAssemble = Renderer::InputAssemble::Create();
    _pInputAssemble->SetInputLayout(VertLayout);
    _pInputAssemble->SetVertexBuffer(Vert.data(), Vert.size());
    _pInputAssemble->SetIndexBuffer(Indices.data(), Indices.size());
}

const Ptr<Renderer::InputAssemble>& Quad::GetInputAssemble() const
{
    return _pInputAssemble;
}
