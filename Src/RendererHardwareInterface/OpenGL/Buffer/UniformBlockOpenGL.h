#pragma once

#include "Renderer/Buffer/UniformBlock.h"

namespace Renderer
{
    class UniformBlockOpenGL: public UniformBlock
    {
    public:
        explicit UniformBlockOpenGL(const std::string& name);

    public:
        void UpdateOffset() override;

    private:
        static constexpr int STD140_ALIGN = 16;
    };
}