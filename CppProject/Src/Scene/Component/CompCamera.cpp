#include "CompCamera.h"
#include "Camera/OrthoCamera.h"

CompCamera::CompCamera(float left, float right, float bottom, float top, float near, float far)
    : _pCamera(std::make_unique<OrthoCamera>(left, right, bottom, top, near, far))
{
}

Camera* CompCamera::GetCamera() const
{
    return _pCamera.get();
}
