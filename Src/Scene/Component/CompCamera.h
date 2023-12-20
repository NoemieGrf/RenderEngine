#pragma once

#include "Component.h"
#include "Scene/Camera/Camera.h"

class CompCamera: public ComponentWithType<ComponentType::Camera>
{
public:
    CompCamera(const Eigen::Vector2f& nearPlaneRightTop, float nearPlaneZ, float farPlaneZ, bool isPerspective = true);
    CompCamera(float fovAngle, float aspect, float nearPlaneZ, float farPlaneZ, bool isPerspective = true);

public:
    Camera& GetCamera();
    const Camera& GetCamera() const;
    void OnPositionSet() override;
    void OnRotationSet() override;
    const Eigen::Matrix4f& GetViewMatrix();
    const Eigen::Matrix4f& GetProjectionMatrix();

private:
    // camera
    Camera _camera;

    // view matrix
    bool _needUpdateViewMatrix;
    Eigen::Matrix4f _viewMatrix;
};