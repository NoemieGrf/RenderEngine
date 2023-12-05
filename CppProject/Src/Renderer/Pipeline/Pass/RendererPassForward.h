#pragma once

#include "RendererPass.h"

namespace Renderer
{
    class RendererPassForward : public RendererPass
    {
    public:
        void Init() override;
        void Renderer(const Scene* pScene) override;
    };
}