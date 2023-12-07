#pragma once

#include <string>
#include "Define/Define.h"
#include "AssetsPool.hpp"

namespace Renderer
{
    class Mesh
    {
    public:
        friend class AssetsPool<Mesh>;


    private:
        void Load(const std::string& path);

    };
}