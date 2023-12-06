#pragma once

#include <eigen/Eigen>

namespace Math
{
    class CameraFrustum
    {
    public:
        CameraFrustum(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ);
        CameraFrustum(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ);

    public:
        float GetFieldOfViewAngle() const;
        float GetFieldOfViewRadian() const;
        float GetAspectRatio() const;

        void Adjust(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ);
        void Adjust(float fov, float aspect, float nearPlaneZ, float farPlaneZ);

        Eigen::Matrix4f GetPerspectiveProjectionMatrix() const;
        Eigen::Matrix4f GetOrthoProjectionMatrix() const;

    private:
        float _nearPlaneHalfX = 0;
        float _nearPlaneHalfY;
        float _nearPlaneZ = 0;
        float _farPlaneZ = 0;
        float _fovRadian = 0;
        float _aspect = 0;
    };
}

