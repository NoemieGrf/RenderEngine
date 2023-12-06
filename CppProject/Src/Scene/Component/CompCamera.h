#pragma once

#include "Component.h"
#include "Scene/Camera/Camera.h"

class CompCamera: public ComponentWithType<ComponentType::Camera>
{
public:
    CompCamera(float left, float right, float bottom, float top, float near, float far);

public:
    Camera* GetCamera() const;
    void OnPositionSet() override;
    void OnRotationSet() override;

private:
    UniPtr<Camera> _pCamera;
};