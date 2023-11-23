#pragma once

#include <concepts>

class AppLooper
{
public:
    virtual ~AppLooper() = default;
    virtual void Loop() = 0;
};

template<class T>
concept AppLooperImpl = std::derived_from<T, AppLooper>;