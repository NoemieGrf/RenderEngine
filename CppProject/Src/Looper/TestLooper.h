#pragma once

#include "Application/AppLooper.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Material/Material.h"
#include "Scene/Component/CompRenderer.h"
#include "Scene/Primitive/Quad.h"
#include "Scene/Scene.h"

class TestLooper : public AppLooper
{
public:
    TestLooper();
    ~TestLooper() override = default;

public:
    void RenderLoop() override;
    void EditorLoop() override;

private:
    Scene _scene;
};


