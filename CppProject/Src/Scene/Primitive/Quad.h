#pragma once

#include <array>
#include "Scene/IRendererObject.h"

class Quad : public IRendererObject
{
public:
    Quad();

public:
    const Ptr<Renderer::InputAssemble>& GetInputAssemble() const override;

private:
    Ptr<Renderer::InputAssemble> _pInputAssemble;

};