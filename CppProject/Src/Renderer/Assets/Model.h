#pragma once

#include <unordered_map>
#include "Define/Define.h"
#include "Mesh.h"

namespace Renderer
{
    class Model
    {
    public:
        const std::unordered_map<std::string, Ptr<Mesh>>& GetMeshMap() const;

        static Ptr<Model> Create(const std::string& path);

    private:
        void Load(const std::string& path);

    private:
        std::unordered_map<std::string, Ptr<Mesh>> _meshMap;
    };
}