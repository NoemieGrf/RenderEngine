#pragma once

#include "Renderer/Buffer/UniformBlock.h"

namespace Renderer
{
    class UniformBlockOpenGL: public UniformBlock
    {
    public:
        void UpdateOffset() override;

    private:
        constexpr int STD140_ALIGN = 16;
    };
}