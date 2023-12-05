#pragma once

#include "Component.h"
#include "IComponentType.h"
#include "Camera/Camera.h"

class CompCamera: public Component, public IComponentType<ComponentType::Camera>
{
public:
    CompCamera(float left, float right, float bottom, float top, float near, float far);

public:
    Camera* GetCamera() const;

private:
    UniPtr<Camera> _pCamera;
};