#pragma once

#include "Define/Define.h"

class SceneObject;

class Component
{
public:
    virtual ~Component() = default;

public:
    void SetSceneObject(SceneObject* pObject);
    SceneObject* GetSceneObject();
    const SceneObject* GetSceneObject() const;

protected:
    SceneObject* _pObject = nullptr;
};

