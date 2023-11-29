#pragma once

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
        virtual ~ShaderProgram() = default;

    public:
        template<ShaderType T>
        bool AddShader(const std::string& path);

        template<ShaderType T>
        Ptr<TypeShader<T>> GetShader();

        virtual bool Link() = 0;
        virtual void Bind() = 0;
        virtual void SetUniformMat4(const std::string& name, const Eigen::Matrix4f& mat) = 0;

    protected:
        virtual void AttachShader(ShaderType t) = 0;

    protected:
        umap<ShaderType, Ptr<Shader>> _shaderMap;

    public:
        static Ptr<ShaderProgram> Create();
    };

    template<ShaderType T>
    bool ShaderProgram::AddShader(const std::string& path)
    {
        auto pShader = ShaderPool<T>::GetShader(path);
        if (pShader == nullptr)
            return false;

        _shaderMap[T] = pShader;
        AttachShader(T);
    }

    template<ShaderType T>
    Ptr<TypeShader<T>> ShaderProgram::GetShader()
    {
        auto itr = _shaderMap.find(T);
        if (itr == _shaderMap.end())
            return nullptr;

        return DynamicCast<TypeShader<T>>(itr->second);
    }

}