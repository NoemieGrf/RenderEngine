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
    public:
        friend class AssetsPool<Mesh>;


    private:
        void Load(const std::string& path);

    private:
        std::vector<float> _data;

    };
}