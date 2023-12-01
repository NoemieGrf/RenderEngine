#pragma once

#include <array>
#include <eigen/Eigen>

#include "Define/Define.h"
#include "ShaderType.h"
#include "ShaderPool.hpp"
#include "Shader.h"

namespace Renderer
{
    class ShaderProgram
    {
    public:
        ShaderProgram();
        virtual ~ShaderProgram() = default;

    public:
        template<ShaderType T>
        Ptr<Shader> AddShader(const std::string& path);

        template<ShaderType T>
        Ptr<Shader> GetShader();

        virtual bool Compile() = 0;
        virtual void Bind() = 0;
        virtual void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) = 0;

    protected:
        virtual void AttachShader(const Ptr<Shader>& pShader) = 0;

    protected:
        std::array<Ptr<Shader>, (int)ShaderType::Count> _shaderArray;

    public:
        static Ptr<ShaderProgram> Create();
    };

    template<ShaderType T>
    Ptr<Shader> ShaderProgram::AddShader(const std::string& path)
    {
        auto pShader = ShaderPool<T>::GetShader(path);
        if (pShader == nullptr)
            return nullptr;

        _shaderArray[(int)T] = pShader;
        AttachShader(pShader);

        return pShader;
    }

    template<ShaderType T>
    Ptr<Shader> ShaderProgram::GetShader()
    {
        return _shaderArray[(int)T];
    }

}