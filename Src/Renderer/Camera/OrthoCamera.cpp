#include "OrthoCamera.h"

namespace Renderer
{
    OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
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

    void OrthoCamera::UpdateViewProjectionMatrix()
    {

    }
}