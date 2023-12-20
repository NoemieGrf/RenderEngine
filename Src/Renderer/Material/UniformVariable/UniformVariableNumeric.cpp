#include "UniformVariableNumeric.h"

namespace Renderer
{
    template<>
    UniformVariableType UniformVariableNumeric<int>::GetType()
    {
        return UniformVariableType::Float;
    }

    template<>
    void UniformVariableNumeric<int>::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        pShader->SetUniformInt(_name, _value);
    }

    template<>
    UniformVariableType UniformVariableNumeric<unsigned int>::GetType()
    {
        return UniformVariableType::Uint;
    }

    template<>
    void UniformVariableNumeric<unsigned int>::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        pShader->SetUniformUnsignedInt(_name, _value);
    }

    template<>
    UniformVariableType UniformVariableNumeric<float>::GetType()
    {
        return UniformVariableType::Float;
    }

    template<>
    void UniformVariableNumeric<float>::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        pShader->SetUniformFloat(_name, _value);
    }

    template<>
    UniformVariableType UniformVariableNumeric<Eigen::Vector2f>::GetType()
    {
        return UniformVariableType::Float2;
    }

    template<>
    void UniformVariableNumeric<Eigen::Vector2f>::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        pShader->SetUniformFloat2(_name, _value);
    }

    template<>
    UniformVariableType UniformVariableNumeric<Eigen::Vector3f>::GetType()
    {
        return UniformVariableType::Float3;
    }

    template<>
    void UniformVariableNumeric<Eigen::Vector3f>::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        pShader->SetUniformFloat3(_name, _value);
    }

    template<>
    UniformVariableType UniformVariableNumeric<Eigen::Vector4f>::GetType()
    {
        return UniformVariableType::Float4;
    }

    template<>
    void UniformVariableNumeric<Eigen::Vector4f>::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        pShader->SetUniformFloat4(_name, _value);
    }

}