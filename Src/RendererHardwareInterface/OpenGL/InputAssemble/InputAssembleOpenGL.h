#pragma once

#include "Renderer/InputAssemble/InputAssemble.h"

namespace Renderer
{
    class InputAssembleOpenGL : public InputAssemble
    {
    public:
        InputAssembleOpenGL();
        ~InputAssembleOpenGL() override;

    public:
        void Bind() override;
        void UnBind() override;

    private:
        unsigned int _vertexArrayId = 0;
    };
}