#pragma once

#include "UniformVariable.h"

namespace Renderer
{
    template<typename T>
    class UniformVariableNumeric: public UniformVariable
    {
    public:
        UniformVariableNumeric(const std::string& name, const T& value)
            : _name(name)
            , _value(value)
        {
        }

    public:
        void Bind() override
        {
        }

        // imp in cpp file
        UniformVariableType GetType() override;

        void SetUniform(Ptr<ShaderProgram>& pShader) override;

    private:
        std::string _name;
        T _value;
    };
}