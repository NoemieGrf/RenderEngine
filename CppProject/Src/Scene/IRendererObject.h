#pragma once
#include "Renderer/Buffer/InputAssemble.h"

class IRendererObject
{
public:
    virtual const Ptr<Renderer::InputAssemble>& GetInputAssemble() const = 0;
};

template<class T>
concept IRendererObjectImp = std::derived_from<T, IRendererObject>;