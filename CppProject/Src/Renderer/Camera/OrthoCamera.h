#pragma once

#include <eigen/Eigen>
#include "Camera.h"

namespace Renderer
{
    class OrthoCamera: public Camera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top, float near, float far);
        ~OrthoCamera() override = default;

    public:
        void SetPosition(const Eigen::Vector3f& pos);
        void SetRotation(float rot);
        const Eigen::Matrix4f& GetProjectionMatrix() const;
        const Eigen::Matrix4f& GetViewMatrix() const;
        const Eigen::Vector3f& GetPosition() const;
        float GetRotation() const;

    public:
        static Eigen::Matrix4f MakeOrthoCameraProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

    private:
        void UpdateViewProjectionMatrix();

    private:
        Eigen::Matrix4f _projectionMatrix;
        Eigen::Matrix4f _viewMatrix;

        Eigen::Matrix4f _cachedViewProjectionMatrix;

        Eigen::Vector3f _position;
        float _rotation = 0;

    };
}