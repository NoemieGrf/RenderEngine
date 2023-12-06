#include "Camera.h"
#include "Math/Math.h"

Camera::Camera(float left, float right, float bottom, float top, float near, float far)
        : _frustum({left, right, bottom, top, near, far})
        , _needUpdateProjectionMatrix(true)
        , _needUpdateViewMatrix(true)
        , _needUpdateCachedVPMatrix(true)
{
}

void Camera::SetPosition(const Eigen::Vector3f& pos)
{
    _position = pos;
    SetNeedUpdateViewMatrix();
}

void Camera::SetRotation(const Eigen::Quaternionf& rot)
{
    _rotation = rot;
    SetNeedUpdateViewMatrix();
}

void Camera::SetFrustum(const Frustum& frustum)
{
    _frustum = frustum;
    SetNeedUpdateProjectionMatrix();
}

const Eigen::Vector3f& Camera::GetPosition() const
{
    return _position;
}

const Eigen::Quaternionf& Camera::GetRotation() const
{
    return _rotation;
}

const Camera::Frustum& Camera::GetFrustum() const
{
    return _frustum;
}

const Eigen::Matrix4f& Camera::GetProjectionMatrix()
{
    UpdateProjectionMatrix();
    return _projectionMatrix;
}

const Eigen::Matrix4f& Camera::GetViewMatrix()
{
    UpdateViewMatrix();
    return _viewMatrix;
}

const Eigen::Matrix4f& Camera::GetVPMatrix()
{
    UpdateViewProjectionMatrix();
    return _cachedViewProjectionMatrix;
}

void Camera::UpdateViewProjectionMatrix()
{
    if (!_needUpdateCachedVPMatrix)
        return;

    _needUpdateCachedVPMatrix = false;

    UpdateProjectionMatrix();
    UpdateViewMatrix();

    _cachedViewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void Camera::UpdateViewMatrix()
{
    if (!_needUpdateViewMatrix)
        return;

    _needUpdateViewMatrix = false;
    _viewMatrix = Math::MakeViewMatrix(_position, _rotation);
}

void Camera::UpdateProjectionMatrix()
{
    if (!_needUpdateProjectionMatrix)
        return;

    _needUpdateProjectionMatrix = false;
    UpdateProjectionMatrixImp();
}

void Camera::SetNeedUpdateProjectionMatrix()
{
    _needUpdateProjectionMatrix = true;
    _needUpdateCachedVPMatrix = true;
}

void Camera::SetNeedUpdateViewMatrix()
{
    _needUpdateViewMatrix = true;
    _needUpdateCachedVPMatrix = true;
}