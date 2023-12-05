#pragma once

#include "Application/AppLooper.h"
#include "Renderer/Camera/OrthoCamera.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Material/Material.h"
#include "Scene/RendererObject.hpp"
#include "Scene/Primitive/Quad.h"

class TestLooper : public AppLooper
{
public:
    TestLooper();
    ~TestLooper() override = default;

public:
    void RenderLoop() override;
    void EditorLoop() override;

private:
    Renderer::OrthoCamera _orthoCamera;
    RendererObject<Quad> _quad;
    Ptr<Renderer::Material> _pQuadMat;
};


