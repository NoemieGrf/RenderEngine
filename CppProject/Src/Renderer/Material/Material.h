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

    private:
        Ptr<ShaderProgram> _pShader;
        std::vector<Ptr<UniformVariable>> _uniVars;
    };
}