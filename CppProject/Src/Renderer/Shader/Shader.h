#pragma once

#include <eigen/Eigen>

#include "Define/Define.h"
#include "Renderer/Shader/SpecificShader/VertexShader.h"
#include "Renderer/Shader/SpecificShader/PixelShader.h"

namespace Renderer
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

    public:
        void AddVertexShader(const char* vertexShaderSource);
        void AddPixelShader(const char* pixelShaderSource);
        virtual bool Link() = 0;
        virtual void Bind() = 0;
        virtual void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) = 0;

    protected:
        virtual void AttachVertexShader() = 0;
        virtual void AttachPixelShader() = 0;

    protected:
        Ptr<VertexShader> _pVertexShader = nullptr;
        Ptr<PixelShader> _pPixelShader = nullptr;

    public:
        static Ptr<Shader> Create();
    };
}