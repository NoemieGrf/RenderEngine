#pragma once

#include <string>
#include <vector>
#include "Define/Define.h"
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
        explicit UniformBlock(const std::string& name);

    public:
        static Ptr<UniformBlock> Create(const std::string& name);

    public:
        void Set(const std::initializer_list<Element>& elements);
        virtual void UpdateOffset() = 0;

    protected:
        std::string _name;
        std::vector<Element> _uniformData;
        XXHashMap<std::string, int> _uniformOffsetMap;
        int _totalSize = 0;
    };
}