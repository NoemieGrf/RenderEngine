#pragma once

#include <concepts>

class AppLooper
{
public:
    virtual ~AppLooper() = default;
    virtual void RenderLoop() = 0;
    virtual void EditorLoop() = 0;
};

template<class T>
concept AppLooperImpl = std::derived_from<T, AppLooper>;