#include "CompCamera.h"
#include "Scene/SceneObject.h"
#include "Math/Math.h"

CompCamera::CompCamera(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ, bool isPerspective)
    : _camera(nearPlaneRightTop, nearPlaneZ, farPlaneZ, isPerspective)
    , _needUpdateViewMatrix(true)
{
}

CompCamera::CompCamera(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ, bool isPerspective)
    : _camera(fovAngle, aspect, nearPlaneZ, farPlaneZ, isPerspective)
    , _needUpdateViewMatrix(true)
{
}


Camera& CompCamera::GetCamera()
{
    return _camera;
}

const Camera& CompCamera::GetCamera() const
{
    return _camera;
}

void CompCamera::OnPositionSet()
{
    _needUpdateViewMatrix = true;
}

void CompCamera::OnRotationSet()
{
    _needUpdateViewMatrix = true;
}

const Eigen::Matrix4f& CompCamera::GetViewMatrix()
{
    if (_needUpdateViewMatrix)
    {
        _needUpdateViewMatrix = false;
        _viewMatrix = Math::MakeViewMatrix(_pObject->GetPosition(), _pObject->GetRotation());
    }

    return _viewMatrix;
}

const Eigen::Matrix4f& CompCamera::GetProjectionMatrix()
{
    return _camera.GetProjectionMatrix();
}



