#pragma once

#include "Application/AppLooper.h"
#include "Renderer/Camera/OrthoCamera.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Material/Material.h"

class TestLooper : public AppLooper
{
public:
    TestLooper();
    ~TestLooper() override = default;

public:
    void RenderLoop() override;
    void EditorLoop() override;

private:
    void PrepareTriangle();
    void PrepareBox();

private:
    Renderer::OrthoCamera _orthoCamera;

    /* Triangle */
    Ptr<Renderer::InputAssemble> _pTriangleInputAssemble;
    Ptr<Renderer::Material> _pTriangleMaterial;

    /* Box */
    std::vector<Ptr<Renderer::InputAssemble>> _boxVertexArrayVec;
    Ptr<Renderer::Material> _BoxMaterial;
};


