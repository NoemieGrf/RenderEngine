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
        virtual void Bind() = 0;
        virtual UniformVariableType GetType() = 0;
        virtual void SetUniform(Ptr<ShaderProgram>& pShader) = 0;
    };

}