#pragma once

#include <Helper/NonConstructible.h>

#include "Define/Define.h"
#include "Scene/SceneObject.h"

class PrimitiveObject: public Helper::NonConstructible
{
public:
    static Ptr<SceneObject> CreateQuad();
    static Ptr<SceneObject> CreateCube();

private:
    static Ptr<SceneObject> LoadFromObj(const std::string& path);
};