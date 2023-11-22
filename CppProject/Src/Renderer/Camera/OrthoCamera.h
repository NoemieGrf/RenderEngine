#pragma once

#include "Camera.h"

namespace Renderer
{
    class OrthoCamera: public Camera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top, float near, float far);
        ~OrthoCamera() override = default;

    public:
        void UpdateProjectionMatrixImp() override;

    };
}