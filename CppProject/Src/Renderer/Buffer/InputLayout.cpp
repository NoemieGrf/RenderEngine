#include "InputLayout.h"

namespace Renderer
{
    InputLayout::InputLayout(const std::initializer_list<InputLayoutElement>& inputLayout)
        : _layout(inputLayout)
        , _stride(0)
    {
        unsigned int offset = 0;
        for (auto& eachLayout : _layout)
        {
            eachLayout.offset = offset;
            offset += eachLayout.size;
            _stride += eachLayout.size;
        }
    }

    const std::vector<InputLayoutElement>& InputLayout::GetLayout() const
    {
        return _layout;
    }

    unsigned int InputLayout::GetStride() const
    {
        return _stride;
    }
}