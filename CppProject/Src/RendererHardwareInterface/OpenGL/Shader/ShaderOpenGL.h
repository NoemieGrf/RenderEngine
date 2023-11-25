#pragma once

#include "Renderer/Shader/Shader.h"

namespace Renderer
{
    class ShaderProgramOpenGL: public Shader
    {
    public:
        ShaderProgramOpenGL();

    public:
        void AttachVertexShader() override;
        void AttachPixelShader() override;
        bool Link() override;
        void Bind() override;
        void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) override;

    private:
        unsigned int _shaderProgramId = 0;
    };
}