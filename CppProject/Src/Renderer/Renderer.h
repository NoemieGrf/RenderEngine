#pragma once

#include "Util/NonCopyable.h"
#include "Define/RendererApi.h"
#include "Renderer/RenderCommand/RenderCommand.h"

namespace Renderer
{
    class Renderer: public NonCopyable
    {
    public: // static
        static void SetApi(RendererApi api);
        static RendererApi GetApi();

    public:
        void Render(RenderCommand* pCommand);

    private:
        inline static RendererApi _api;
    };
}