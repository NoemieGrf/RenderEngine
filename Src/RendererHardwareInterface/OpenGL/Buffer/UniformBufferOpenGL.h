#pragma once

#include "Renderer/Buffer/UniformBuffer.h"

namespace Renderer
{
    class UniformBufferOpenGL: public UniformBuffer
    {
    public:


    private:
        unsigned int _bindingPoint = 0;
    };
}