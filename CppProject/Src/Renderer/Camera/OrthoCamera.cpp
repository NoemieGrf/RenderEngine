#include "OrthoCamera.h"

namespace Renderer
{
    OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
        : _projectionMatrix(MakeOrthoCameraProjectionMatrix(left, right, bottom, top, near, far))
    {
        // todo
    }

    void OrthoCamera::SetPosition(const Eigen::Vector3f& pos)
    {
        _position = pos;
        UpdateViewProjectionMatrix();
    }

    void OrthoCamera::SetRotation(float rot)
    {
        _rotation = rot;
        UpdateViewProjectionMatrix();
    }

    const Eigen::Matrix4f& OrthoCamera::GetProjectionMatrix() const
    {
        return _projectionMatrix;
    }

    const Eigen::Matrix4f& OrthoCamera::GetViewMatrix() const
    {
        return _viewMatrix;
    }

    const Eigen::Vector3f& OrthoCamera::GetPosition() const
    {
        return _position;
    }

    float OrthoCamera::GetRotation() const
    {
        return _rotation;
    }

    Eigen::Matrix4f OrthoCamera::MakeOrthoCameraProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();

        // Translation
        result.col(3) = Eigen::Vector4f {
            -(right + left) / (right - left),
            -(top + bottom) / (top - bottom),
            -(near + far) / (near - far),
            1
        };

        // Scale
        result(0, 0) = 2 / (right - left);
        result(1, 1) = 2 / (top - bottom);
        result(2, 2) = 2 / (near - far);

        return result;
    }

    void OrthoCamera::UpdateViewProjectionMatrix()
    {

    }
}