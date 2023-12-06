#include "SceneObject.h"
#include "Math/Math.h"

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

const Eigen::Matrix4f& SceneObject::GetModelMatrix()
{
    if (_needUpdateModelMatrix)
    {
        _needUpdateModelMatrix = false;
        _modelMatrix = Math::MakeModelMatrix(_position, _rotation, _scale);
    }

    return _modelMatrix;
}

void SceneObject::SetPosition(const Eigen::Vector3f& position)
{
    _position = position;
    _needUpdateModelMatrix = true;

    for (auto& [key, pComp]: _componentMap)
    {
        if (pComp != nullptr)
            pComp->OnPositionSet();
    }
}

void SceneObject::SetRotation(const Eigen::Quaternionf& rotation)
{
    _rotation = rotation;
    _needUpdateModelMatrix = true;

    for (auto& [key, pComp]: _componentMap)
    {
        if (pComp != nullptr)
            pComp->OnRotationSet();
    }
}

void SceneObject::SetScale(const Eigen::Vector3f& scale)
{
    _scale = scale;
    _needUpdateModelMatrix = true;

    for (auto& [key, pComp]: _componentMap)
    {
        if (pComp != nullptr)
            pComp->OnScaleSet();
    }
}
