#pragma once

#include "Renderer/Shader/SpecificShader/VertexShader.h"

namespace Renderer
{
    class VertexShaderOpenGL : public VertexShader
    {
    public:
        ~VertexShaderOpenGL() override;

    public: // override
        bool Compile() override;
        void LoadFromString(const char* data) override;

    public:
        unsigned int GetShaderId() const;

    private:
        unsigned int _shaderId = 0;
    };
}