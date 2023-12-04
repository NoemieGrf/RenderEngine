#pragma once

#include "Application/AppLooper.h"
#include "Renderer/Camera/OrthoCamera.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Texture/Texture2d.h"

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

    /* Triangle */
    Ptr<Renderer::ShaderProgram> _pTriangleShader;
    Ptr<Renderer::VertexArray> _pTriangleVertexArray;
    Ptr<Renderer::Texture2d> _pTriangleTexture;
    Ptr<Renderer::Texture2d> _pTriangleTexture2;
};


