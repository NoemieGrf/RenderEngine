#pragma once

#include "Application/AppLooper.h"
#include "Renderer/RenderCommand/RenderCommand.h"

class RenderLooper : public AppLooper
{
public:
    RenderLooper();
    ~RenderLooper() override;

public:
    void Loop() override;

private:
    /* Rhi */
    Renderer::RenderCommand* _pRenderCommand;

private:

};


