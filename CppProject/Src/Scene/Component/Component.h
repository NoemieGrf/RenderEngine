#pragma once

#include "Define/Define.h"
#include "ComponentType.h"

class SceneObject;

class Component
{
public:
    virtual ~Component() = default;

public:
    void SetSceneObject(SceneObject* pObject);
    SceneObject* GetSceneObject();
    const SceneObject* GetSceneObject() const;

public:
    virtual void OnPositionSet();
    virtual void OnRotationSet();
    virtual void OnScaleSet();

protected:
    SceneObject* _pObject = nullptr;
};

template<ComponentType type>
class ComponentWithType: public Component
{
public:
    static ComponentType GetType()
    {
        return type;
    }
};

