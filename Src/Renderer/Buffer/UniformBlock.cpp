#include "UniformBlock.h"

namespace Renderer
{
    UniformBlock::UniformBlock(const std::initializer_list<Element>& elements)
        : _uniformData(elements)
    {
    }
}
