#include "SceneObject.h"
#include "Math/Math.h"

const Eigen::Vector3f& SceneObject::GetLocalPosition() const
{
    return _position;
}

const Eigen::Quaternionf& SceneObject::GetLocalRotation() const
{
    return _rotation;
}

const Eigen::Vector3f& SceneObject::GetLocalScale() const
{
    return _scale;
}

const Eigen::Matrix4f& SceneObject::GetModelMatrix()
{
    if (_needUpdateModelMatrix)
    {
        _needUpdateModelMatrix = false;
        _modelMatrix = Math::MakeModelMatrix(GetWorldPosition(), GetWorldRotation(), GetWorldScale());
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
const std::string& SceneObject::GetName() const
{
    return _name;
}

void SceneObject::SetName(const std::string& name)
{
    _name = name;
}

void SceneObject::AddChild(const Ptr<SceneObject>& pChild)
{
    const Eigen::Vector3f& oldWorldPosition = pChild->GetWorldPosition();
    const Eigen::Quaternionf& oldWorldRotation = pChild->GetWorldRotation();
    const Eigen::Vector3f& oldWorldScale = pChild->GetWorldScale();

    if (!_childrenObjects.contains(pChild))
        _childrenObjects.insert(pChild);

    Eigen::Vector3f diffLocalPosition = GetWorldPosition() - oldWorldPosition;
    pChild->SetPosition(diffLocalPosition);

    Eigen::Quaternionf diffLocalRotation = GetWorldRotation().inverse() * oldWorldRotation;
    pChild->SetRotation(diffLocalRotation);

    Eigen::Vector3f diffLocalScale = oldWorldScale / GetWorldScale();
    pChild->SetScale(diffLocalScale);
}

const uset<Ptr<SceneObject>>& SceneObject::GetAllChildren()
{
    return _childrenObjects;
}

void SceneObject::OnParentPositionChanged()
{
    _needUpdateModelMatrix = true;

    for (auto& [key, pComp]: _componentMap)
    {
        if (pComp != nullptr)
            pComp->OnPositionSet();
    }
}

void SceneObject::OnParentRotationChanged()
{
    _needUpdateModelMatrix = true;

    for (auto& [key, pComp]: _componentMap)
    {
        if (pComp != nullptr)
            pComp->OnRotationSet();
    }
}

void SceneObject::OnParentScaleChanged()
{
    _needUpdateModelMatrix = true;

    for (auto& [key, pComp]: _componentMap)
    {
        if (pComp != nullptr)
            pComp->OnScaleSet();
    }
}
