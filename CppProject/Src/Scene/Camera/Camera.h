#pragma once

#include "eigen/Eigen"
#include "Math/CameraFrustum.h"

class Camera
{
public:
    Camera(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ, bool isPerspective = true);
    Camera(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ, bool isPerspective = true);
    virtual ~Camera() = default;

public:
    void SetPosition(const Eigen::Vector3f& pos);
    void SetRotation(const Eigen::Quaternionf& rot);
    const Eigen::Vector3f& GetPosition() const;
    const Eigen::Quaternionf& GetRotation() const;
    const Math::CameraFrustum& GetFrustum() const;
    Math::CameraFrustum& GetFrustum();

    const Eigen::Matrix4f& GetProjectionMatrix();
    const Eigen::Matrix4f& GetViewMatrix();
    const Eigen::Matrix4f& GetVPMatrix();

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

protected:
    void UpdateViewProjectionMatrix();

private:
    void SetNeedUpdateProjectionMatrix();
    void SetNeedUpdateViewMatrix();

protected:
    // bool
    bool _isPerspective;

    // projection matrix
    Math::CameraFrustum _frustum;
    Eigen::Matrix4f _projectionMatrix;

    // view matrix
    Eigen::Vector3f _position = Eigen::Vector3f::Zero();
    Eigen::Quaternionf _rotation = Eigen::Quaternionf::Identity();
    Eigen::Matrix4f _viewMatrix;

    // cache
    Eigen::Matrix4f _cachedViewProjectionMatrix;

private:
    bool _needUpdateProjectionMatrix;
    bool _needUpdateViewMatrix;
    bool _needUpdateCachedVPMatrix;
};