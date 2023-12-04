#pragma once

#include <cassert>
#include "Define/Define.h"
#include "UniformVariableType.h"
#include "Renderer/Shader/ShaderProgram.h"

namespace Renderer
{
    class UniformVariable
    {
    public:
        virtual UniformVariableType GetType() = 0;
        virtual void SetUniform(const Ptr<ShaderProgram>& pShader) = 0;
    };

}