#pragma once

#include <string>
#include <array>
#include "Define/Define.h"
#include "Renderer/InputAssemble/InputLayout.h"
#include "AssetsPool.hpp"

namespace Renderer
{
    class Mesh
    {
        friend class Model;

    public:
        const std::vector<float>& GetVertexData() const;
        const std::vector<unsigned int>& GetIndexData() const;
        const InputLayout& GetLayout() const;

    private:
        std::vector<float> _vertexData;
        std::vector<unsigned int> _indexData;
        InputLayout _dataLayout;
    };
}