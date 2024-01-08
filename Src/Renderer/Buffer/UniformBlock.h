#pragma once

#include <string>
#include <vector>
#include "ThirdParty/XXHash/XXHashMap.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    class UniformBlock
    {
    public:
        struct Element
        {
            std::string name;
            ShaderDataType shaderDataType;
        };

    public:
        virtual ~UniformBlock() = default;
        UniformBlock(const std::initializer_list<Element>& elements);

    public:
        virtual void UpdateOffset() = 0;

    protected:
        std::vector<Element> _uniformData;
        XXHashMap<std::string, int> _uniformOffsetMap;
        int _totalSize = 0;
    };
}