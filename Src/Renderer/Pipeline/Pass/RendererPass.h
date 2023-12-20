#pragma once

#include "Define/Define.h"
#include "RendererPassType.h"

class Scene;

namespace Renderer
{
    class RendererPass
    {
    public:
        virtual void Init() = 0;
        virtual void Renderer(const Scene* pScene) = 0;
    };
}