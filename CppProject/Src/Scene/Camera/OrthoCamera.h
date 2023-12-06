#pragma once

#include "Camera.h"

class OrthoCamera: public Camera
{
public:
    OrthoCamera(float left, float right, float bottom, float top, float near, float far);
    ~OrthoCamera() override = default;

public:
    void UpdateProjectionMatrixImp() override;

};