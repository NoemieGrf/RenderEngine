#pragma once

#include <array>
#include <eigen/Eigen>

#include "Define/Define.h"
#include "ShaderType.h"
#include "Shader.h"
#include "Renderer/Assets/AssetsPool.hpp"
#include "Renderer/Shader/SpecificShader/VertexShader.h"
#include "Renderer/Shader/SpecificShader/PixelShader.h"

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
        virtual void SetUniformInt(const std::string& name, int value) = 0;
        virtual void SetUniformUnsignedInt(const std::string& name, unsigned int value) = 0;
        virtual void SetUniformFloat(const std::string& name, float value) = 0;
        virtual void SetUniformMat3(const std::string& name, const Eigen::Matrix3f& mat) = 0;
        virtual void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) = 0;

    protected:
        virtual void AttachShader(const Ptr<Shader>& pShader) = 0;

    protected:
        std::array<Ptr<Shader>, static_cast<int>(ShaderType::Count)> _shaderArray;

    public:
        static Ptr<ShaderProgram> Create();
    };

    template<ShaderType T>
    Ptr<Shader> ShaderProgram::AddShader(const std::string& path)
    {
        Ptr<Shader> pShader = nullptr;
        if constexpr (T == ShaderType::Vertex)
            pShader = AssetsPool<VertexShader>::Get(path);
        else if constexpr (T == ShaderType::Pixel)
            pShader = AssetsPool<PixelShader>::Get(path);

        if (pShader == nullptr)
            return nullptr;

        _shaderArray[static_cast<int>(T)] = pShader;
        AttachShader(pShader);

        return pShader;
    }

    template<ShaderType T>
    Ptr<Shader> ShaderProgram::GetShader()
    {
        return _shaderArray[static_cast<int>(T)];
    }

}