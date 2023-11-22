#pragma once

#include "Renderer/Shader/PixelShader.h"

namespace Renderer
{
    class PixelShaderOpenGL : public PixelShader
    {
    public:
        ~PixelShaderOpenGL() override;

    public: // override
        bool Compile() override;
        void LoadFromString(const char* data) override;

    public:
        unsigned int GetShaderId() const;

    private:
        unsigned int _shaderId = 0;
    };
}