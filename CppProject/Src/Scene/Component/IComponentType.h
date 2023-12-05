#pragma once

#include "ComponentType.h"

template<ComponentType type>
class IComponentType
{
public:
    static ComponentType GetType()
    {
        return type;
    }
};