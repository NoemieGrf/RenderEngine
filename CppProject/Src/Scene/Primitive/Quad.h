#pragma once

#include <array>
#include "Renderer/Buffer/InputAssemble.h"

class Quad
{
public:
    Quad();

public:
    Ptr<Renderer::InputAssemble> GetVertexBuffer() const;

private:
    Ptr<Renderer::InputAssemble> _pVertexBuffer;

};