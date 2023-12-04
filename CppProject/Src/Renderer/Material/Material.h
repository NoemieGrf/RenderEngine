#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "UniformVariable/UniformVariable.h"

namespace Renderer
{
    class Material
    {
    public:
        explicit Material(const std::string& materialPath);

    public:
        void Bind();
        void SetUniform();
        Ptr<ShaderProgram> GetShader() const;
        const std::vector<Ptr<UniformVariable>>& GetUniformVariables() const;

    private:
        Ptr<ShaderProgram> _pShader;
        std::vector<Ptr<UniformVariable>> _uniVars;
    };
}