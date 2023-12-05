#pragma once

#include <string>
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    struct InputLayoutElement
    {
        std::string name;
        ShaderDataType dataType;
        unsigned int size;
        unsigned int offset;
        bool normalized;

        explicit InputLayoutElement(ShaderDataType type, const std::string& name, bool normalized = false);
    };
}