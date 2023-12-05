#include "SceneObject.h"

Eigen::Vector3f& SceneObject::GetPosition()
{
    return _position;
}

Eigen::Quaternionf& SceneObject::GetRotation()
{
    return _rotation;
}

Eigen::Vector3f& SceneObject::GetScale()
{
    return _scale;
}
