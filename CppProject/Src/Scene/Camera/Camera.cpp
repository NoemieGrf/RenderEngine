#include <numbers>
#include <cmath>
#include "Camera.h"
#include "Math/Math.h"
#include "Application/Application.h"

Camera::Camera(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ, bool isPerspective)
    : _isPerspective(isPerspective)
    , _needUpdateProjectionMatrix(true)
{
    Adjust(nearPlaneRightTop, nearPlaneZ, farPlaneZ);
}

Camera::Camera(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ, bool isPerspective)
    : _isPerspective(isPerspective)
    , _needUpdateProjectionMatrix(true)
{
    Adjust(fovAngle, aspect, nearPlaneZ, farPlaneZ);
}

float Camera::GetNearPlaneHalfX() const
{
    return _nearPlaneHalfX;
}

float Camera::GetNearPlaneHalfY() const
{
    return _nearPlaneHalfY;
}

float Camera::GetNearPlaneZ() const
{
    return _nearPlaneZ;
}

float Camera::GetFarPlaneZ() const
{
    return _farPlaneZ;
}

float Camera::GetFieldOfViewAngle() const
{
    return _fovRadian * 180 / std::numbers::pi;
}

float Camera::GetFieldOfViewRadian() const
{
    return _fovRadian;
}

float Camera::GetAspectRatio() const
{
    return _aspect;
}

void Camera::Adjust(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ)
{
    assert(nearPlaneRightTop.x() > 0);
    assert(nearPlaneRightTop.y() > 0);
    assert(farPlaneZ < nearPlaneZ && nearPlaneZ < 0); // look at -z, right handed coordinates

    _nearPlaneHalfX = nearPlaneRightTop.x();
    _nearPlaneHalfY = nearPlaneRightTop.y();
    _nearPlaneZ = nearPlaneZ;
    _farPlaneZ = farPlaneZ;

    _aspect = _nearPlaneHalfY / _nearPlaneHalfX;
    _fovRadian = 2 * std::atan(static_cast<double>(_nearPlaneHalfX) / (-nearPlaneZ));

    _needUpdateProjectionMatrix = true;
}

void Camera::Adjust(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ)
{
    assert(aspect > 0);
    assert(fovAngle > 0 && fovAngle < 180);
    assert(farPlaneZ < nearPlaneZ && nearPlaneZ < 0); // look at -z, right handed coordinates

    _fovRadian = (fovAngle * std::numbers::pi / 180) / 2;
    _aspect = aspect;
    _nearPlaneZ = nearPlaneZ;
    _farPlaneZ = farPlaneZ;

    _nearPlaneHalfX = (-nearPlaneZ) * std::tan(_fovRadian);
    _nearPlaneHalfY = _aspect * _nearPlaneHalfX;

    _needUpdateProjectionMatrix = true;
}

const Eigen::Matrix4f& Camera::GetProjectionMatrix()
{
    if (_needUpdateProjectionMatrix)
    {
        _needUpdateProjectionMatrix = false;

        auto api = Application::GetRenderApi();
        if (_isPerspective)
            _projectionMatrix = Math::MakePerspectiveProjectionMatrix(api, _nearPlaneHalfX, _nearPlaneHalfY, _nearPlaneZ, _farPlaneZ);
        else
            _projectionMatrix = Math::MakeOrthoProjectionMatrix(api, _nearPlaneHalfX, _nearPlaneHalfY, _nearPlaneZ, _farPlaneZ);
    }

    return _projectionMatrix;
}
