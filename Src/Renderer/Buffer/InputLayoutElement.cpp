#include "InputLayoutElement.h"

namespace Renderer
{
    InputLayoutElement::InputLayoutElement(ShaderDataType type, const std::string& name, bool normalized)
            : name(name)
            , dataType(type)
            , size(ShaderDataTypeHelper::GetShaderDataTypeSize(type))
            , offset(0)
            , normalized(normalized)
    {
    }
}
