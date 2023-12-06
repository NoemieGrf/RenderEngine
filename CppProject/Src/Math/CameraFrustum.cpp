#include <numbers>
#include <cmath>
#include "CameraFrustum.h"

namespace Math
{

    CameraFrustum::CameraFrustum(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ)
    {
        Adjust(nearPlaneRightTop, nearPlaneZ, farPlaneZ);
    }

    CameraFrustum::CameraFrustum(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ)
    {
        Adjust(fovAngle, aspect, nearPlaneZ, farPlaneZ);
    }

    float CameraFrustum::GetFieldOfViewAngle() const
    {
        return _fovRadian * 180 / std::numbers::pi;
    }

    float CameraFrustum::GetFieldOfViewRadian() const
    {
        return _fovRadian;
    }

    float CameraFrustum::GetAspectRatio() const
    {
        return _aspect;
    }

    void CameraFrustum::Adjust(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ)
    {
        assert(nearPlaneRightTop.x() > 0);
        assert(nearPlaneRightTop.y() > 0);
        assert(farPlaneZ < nearPlaneZ && nearPlaneZ < 0); // look at -z, right handed coordinates

        _nearPlaneHalfX = nearPlaneRightTop.x();
        _nearPlaneHalfY = nearPlaneRightTop.y();
        _nearPlaneZ = nearPlaneZ;
        _farPlaneZ = farPlaneZ;

        _aspect = (float)_nearPlaneHalfY / _nearPlaneHalfX;
        _fovRadian = 2 * std::atan((double)_nearPlaneHalfX / (-nearPlaneZ));
    }

    void CameraFrustum::Adjust(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ)
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
    }

    Eigen::Matrix4f CameraFrustum::GetPerspectiveProjectionMatrix() const
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();

        result(0, 0) = _nearPlaneZ / _nearPlaneHalfX;
        result(1, 1) = _nearPlaneZ / _nearPlaneHalfY;
        result(2, 3) = - (_farPlaneZ + _nearPlaneZ) / (_farPlaneZ - _nearPlaneZ);
        result(3, 3) = 0;
        result(3, 2) = -1;
        result(2, 3) = -2 * _farPlaneZ * _nearPlaneZ / (_farPlaneZ - _nearPlaneZ);

        return result;
    }

    Eigen::Matrix4f CameraFrustum::GetOrthoProjectionMatrix() const
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();

        result(0, 0) = 1 / _nearPlaneHalfX;
        result(1, 1) = 1 / _nearPlaneHalfY;
        result(2, 2) = 1 / (_farPlaneZ - _nearPlaneZ);
        result(2, 3) = - (_farPlaneZ + _nearPlaneZ) / (_farPlaneZ - _nearPlaneZ);

        return result;
    }
}
