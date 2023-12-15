#pragma once

#include "Renderer/Shader/SpecificShader/VertexShader.h"
#include "RendererHardwareInterface/OpenGL/Shader/IOpenGLShaderId.h"

namespace Renderer
{
    class VertexShaderOpenGL : public VertexShader, public IOpenGLShaderId
    {
    public:
        ~VertexShaderOpenGL() override;

    public: // override
        bool Compile() override;
        void LoadFromString(const char* data) override;
        void LoadFromBinaray(const char* data, int size) override;

    private:
        bool _needCompile = true;
    };
}