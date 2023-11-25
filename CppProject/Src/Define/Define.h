#pragma once

#include <memory>

template<typename T>
using Ptr = std::shared_ptr<T>;

template<typename T>
using UniPtr = std::unique_ptr<T>;

template <class Target, class Source>
std::shared_ptr<Target> DynamicCast(const std::shared_ptr<Source>& src)
{
    return dynamic_pointer_cast<Target>(src);
}

template <class Target, class Source>
std::shared_ptr<Target> DynamicCast(std::shared_ptr<Source>&& src)
{
    return dynamic_pointer_cast<Target>(std::forward<std::shared_ptr<Source>&&>(src));
}



