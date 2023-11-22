#pragma once

#include <eigen/Eigen>

namespace Renderer
{
    class Camera
    {
    public:
        Camera(float left, float right, float bottom, float top, float near, float far);
        virtual ~Camera() = default;

    public:
        void SetPosition(const Eigen::Vector3f& pos);
        void SetRotation(const Eigen::Quaternionf& rot);

        const Eigen::Matrix4f& GetProjectionMatrix();
        const Eigen::Matrix4f& GetViewMatrix();
        const Eigen::Vector3f& GetPosition() const;
        const Eigen::Quaternionf& GetRotation() const;

        void UpdateViewMatrix();
        void UpdateProjectionMatrix();
        virtual void UpdateProjectionMatrixImp() = 0;

    protected:
        void UpdateViewProjectionMatrix();

    private:
        void SetNeedUpdateProjectionMatrix();
        void SetNeedUpdateViewMatrix();

    protected:
        // projection matrix
        float _left;
        float _right;
        float _bottom;
        float _top;
        float _near;
        float _far;
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
}