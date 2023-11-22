#include "Camera.h"
#include "Math/Math.h"

namespace Renderer
{
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
        SetNeedUpdateProjectionMatrix();
    }

    void Camera::SetRotation(const Eigen::Quaternionf& rot)
    {
        _rotation = rot;
        SetNeedUpdateProjectionMatrix();
    }

    void Camera::SetFrustum(const Frustum& frustum)
    {
        _frustum = frustum;
        SetNeedUpdateViewMatrix();
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
}