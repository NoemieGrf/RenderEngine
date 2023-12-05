#pragma once

#include "Define/Define.h"

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