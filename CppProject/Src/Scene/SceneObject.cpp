#include "SceneObject.h"

const Eigen::Vector3f& SceneObject::GetPosition() const
{
    return _position;
}

const Eigen::Quaternionf& SceneObject::GetRotation() const
{
    return _rotation;
}

const Eigen::Vector3f& SceneObject::GetScale() const
{
    return _scale;
}

void SceneObject::SetPosition(const Eigen::Vector3f& position)
{
    _position = position;
}

void SceneObject::SetRotation(const Eigen::Quaternionf& rotation)
{
    _rotation = rotation;
}

void SceneObject::SetScale(const Eigen::Vector3f& scale)
{
    _scale = scale;
}
