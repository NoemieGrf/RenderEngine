#pragma once

#include "Define/Define.h"
#include "Util/NonConstructible.h"
#include "Scene/SceneObject.h"

class PrimitiveObject: public NonConstructible
{
public:
    static Ptr<SceneObject> CreateQuad();
    static Ptr<SceneObject> CreateBox();

private:
    static Ptr<SceneObject> LoadFromObj(const std::string& path);
};