#pragma once

#include "Renderer/Shader/ShaderProgram.h"

namespace Renderer
{
    class ShaderProgramOpenGL: public ShaderProgram
    {
    public:
        ShaderProgramOpenGL();

    public:
        void AddVertexShader(VertexShader* pVertexShader) override;
        void AddPixelShader(PixelShader* pPixelShader) override;
        bool Link() override;
        void Bind() override;
        void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) override;

    private:
        unsigned int _shaderProgramId = 0;
    };
}