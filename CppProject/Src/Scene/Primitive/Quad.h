#pragma once

#include <array>
#include "Renderer/Buffer/InputAssemble.h"

class Quad
{
public:
    Quad();

public:
    Ptr<Renderer::InputAssemble> GetInputAssemble() const;

private:
    Ptr<Renderer::InputAssemble> _pInputAssemble;

};