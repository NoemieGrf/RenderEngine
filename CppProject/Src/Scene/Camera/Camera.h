#pragma once

#include "eigen/Eigen"

class Camera
{
public:
    Camera(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ, bool isPerspective = true);
    Camera(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ, bool isPerspective = true);
    virtual ~Camera() = default;

public:
    float GetNearPlaneHalfX() const;
    float GetNearPlaneHalfY() const;
    float GetNearPlaneZ() const;
    float GetFarPlaneZ() const;
    float GetFieldOfViewAngle() const;
    float GetFieldOfViewRadian() const;
    float GetAspectRatio() const;
    const Eigen::Matrix4f& GetProjectionMatrix();

    void Adjust(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ);
    void Adjust(float fov, float aspect, float nearPlaneZ, float farPlaneZ);

private:
    // bool
    bool _isPerspective;

    // camera frustum
    float _nearPlaneHalfX = 0;
    float _nearPlaneHalfY = 0;
    float _nearPlaneZ = 0;
    float _farPlaneZ = 0;
    float _fovRadian = 0;
    float _aspect = 0;

    // projection matrix
    bool _needUpdateProjectionMatrix;
    Eigen::Matrix4f _projectionMatrix;
};