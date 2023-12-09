#pragma once

#include <string>
#include <vector>

#include "InputLayoutElement.h"

namespace Renderer
{
    class InputLayout
    {
    public:
        InputLayout() = default;
        InputLayout(const std::initializer_list<InputLayoutElement>& inputLayout);
        explicit InputLayout(std::vector<InputLayoutElement>&& inputLayout);

    public:
        const std::vector<InputLayoutElement>& GetLayout() const;
        unsigned int GetStride() const;

    private:
        void UpdateStride();

    private:
        std::vector<InputLayoutElement> _layout;
        unsigned int _stride;
    };
}