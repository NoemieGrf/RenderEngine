#include "Component.h"

void Component::SetSceneObject(SceneObject* pObject)
{
    _pObject = pObject;
}

SceneObject* Component::GetSceneObject()
{
    return _pObject;
}

const SceneObject* Component::GetSceneObject() const
{
    return _pObject;
}

void Component::OnPositionSet()
{
}

void Component::OnRotationSet()
{
}

void Component::OnScaleSet()
{
}
