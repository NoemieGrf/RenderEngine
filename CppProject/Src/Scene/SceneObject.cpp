#include "SceneObject.h"
#include "Math/Math.h"


#include <ranges>

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

    for (auto& pComp: _componentMap | std::views::values)
    {
        if (pComp != nullptr)
            pComp->OnPositionSet();
    }

    for (auto& childObj: _childrenObjects)
    {
        if (childObj != nullptr)
            childObj->OnParentPositionChanged();
    }
}

void SceneObject::SetRotation(const Eigen::Quaternionf& rotation)
{
    _rotation = rotation;
    _needUpdateModelMatrix = true;

    for (auto& pComp: _componentMap | std::views::values)
    {
        if (pComp != nullptr)
            pComp->OnRotationSet();
    }

    for (auto& childObj: _childrenObjects)
    {
        if (childObj != nullptr)
            childObj->OnParentRotationChanged();
    }
}

void SceneObject::SetScale(const Eigen::Vector3f& scale)
{
    _scale = scale;
    _needUpdateModelMatrix = true;

    for (auto& pComp: _componentMap | std::views::values)
    {
        if (pComp != nullptr)
            pComp->OnScaleSet();
    }

    for (auto& childObj: _childrenObjects)
    {
        if (childObj != nullptr)
            childObj->OnParentScaleChanged();
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
    Eigen::Vector3f oldWorldPosition = pChild->GetWorldPosition();
    Eigen::Quaternionf oldWorldRotation = pChild->GetWorldRotation();
    Eigen::Vector3f oldWorldScale = pChild->GetWorldScale();

    if (!_childrenObjects.contains(pChild))
        _childrenObjects.insert(pChild);

    Eigen::Vector3f diffLocalPosition = GetWorldPosition() - oldWorldPosition;
    pChild->SetPosition(diffLocalPosition);

    Eigen::Quaternionf diffLocalRotation = GetWorldRotation().inverse() * oldWorldRotation;
    pChild->SetRotation(diffLocalRotation);

    const Eigen::Vector3f& worldScale = GetWorldScale();
    Eigen::Vector3f diffLocalScale = Eigen::Vector3f{
        oldWorldScale.x() / worldScale.x(),
        oldWorldScale.y() / worldScale.y(),
        oldWorldScale.z() / worldScale.z()
    };

    pChild->SetScale(diffLocalScale);
}

const uset<Ptr<SceneObject>>& SceneObject::GetAllChildren()
{
    return _childrenObjects;
}

void SceneObject::OnParentPositionChanged()
{
    _needUpdateModelMatrix = true;

    for (auto& pComp: _componentMap | std::views::values)
    {
        if (pComp != nullptr)
            pComp->OnPositionSet();
    }
}

void SceneObject::OnParentRotationChanged()
{
    _needUpdateModelMatrix = true;

    for (auto& pComp: _componentMap | std::views::values)
    {
        if (pComp != nullptr)
            pComp->OnRotationSet();
    }
}

void SceneObject::OnParentScaleChanged()
{
    _needUpdateModelMatrix = true;

    for (auto& pComp: _componentMap | std::views::values)
    {
        if (pComp != nullptr)
            pComp->OnScaleSet();
    }
}
Eigen::Vector3f SceneObject::GetWorldPosition() const
{
    if (_parentObject == nullptr)
        return _position;
    else
        return _position + _parentObject->GetWorldPosition();
}

Eigen::Quaternionf SceneObject::GetWorldRotation() const
{
    if (_parentObject == nullptr)
        return _rotation;
    else
        return _parentObject->GetWorldRotation() * _rotation;
}

Eigen::Vector3f SceneObject::GetWorldScale() const
{
    if (_parentObject == nullptr)
        return _scale;
    else
    {
        Eigen::Vector3f parentScale = _parentObject->GetWorldScale();
        return Eigen::Vector3f {
                _scale.x() * parentScale.x(),
                _scale.y() * parentScale.y(),
                _scale.z() * parentScale.z()
        };
    }
}
