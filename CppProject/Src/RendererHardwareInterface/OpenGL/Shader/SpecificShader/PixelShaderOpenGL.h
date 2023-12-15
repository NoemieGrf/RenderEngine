#pragma once

#include "Renderer/Shader/SpecificShader/PixelShader.h"
#include "RendererHardwareInterface/OpenGL/Shader/IOpenGLShaderId.h"

namespace Renderer
{
    class PixelShaderOpenGL : public PixelShader, public IOpenGLShaderId
    {
    public:
        ~PixelShaderOpenGL() override;

    public: // override
        bool Compile() override;
        void LoadFromString(const char* data) override;
        void LoadFromBinaray(const char* data, int size) override;

    private:
        bool _needCompile = true;
    };
}