#pragma once

#include <string>
#include <array>
#include "Define/Define.h"
#include "Renderer/Buffer/InputLayout.h"
#include "AssetsPool.hpp"

namespace Renderer
{
    class Mesh
    {
        friend class Model;

    public:

    private:
        std::vector<float> _vertexData;
        std::vector<float> _indexData;
        InputLayout _dataLayout;
    };
}