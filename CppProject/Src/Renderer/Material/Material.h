#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/Shader.h"

namespace Renderer
{
    class Material
    {
    public:
        explicit Material(const std::string& materialPath);

    private:
        Ptr<Shader> _shader;
    };
}