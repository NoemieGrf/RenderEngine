#pragma once

#include "Application/AppLooper.h"

class TestLooper : public AppLooper
{
public:
    TestLooper() = default;
    ~TestLooper() override = default;

public:
    void RenderLoop() override;
    void EditorLoop() override;
};


