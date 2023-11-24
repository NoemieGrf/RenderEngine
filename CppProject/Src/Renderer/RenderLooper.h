#pragma once

#include "Application/AppLooper.h"

class RenderLooper : public AppLooper
{
public:
    RenderLooper() = default;
    ~RenderLooper() override = default;

public:
    void Loop() override;
};


