#pragma once

#include <eigen/Eigen>

#include "VertexShader.h"
#include "PixelShader.h"


namespace Renderer
{
    class ShaderProgram
    {
    public:
        virtual ~ShaderProgram() = default;

    public:
        virtual void AddVertexShader(VertexShader* pVertexShader) = 0;
        virtual void AddPixelShader(PixelShader* pPixelShader) = 0;
        virtual bool Link() = 0;
        virtual void Bind() = 0;
        virtual void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) = 0;

    public:
        static ShaderProgram* Create();
    };
}