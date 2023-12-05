#pragma once

#include <eigen/Eigen>
#include "IRendererObject.h"

template<IRendererObjectImp T>
class RendererObject
{
public:
    RendererObject()
    {
        _pRendererObject = std::make_shared<T>();
    }

public:
    Ptr<Renderer::InputAssemble> GetInputAssemble() const
    {
        return _pRendererObject->GetInputAssemble();
    }

    const Ptr<T>& GetObject() const
    {
        return _pRendererObject;
    }

protected:
    Eigen::Vector3f _position;
    Eigen::Quaternionf _rotation;
    Eigen::Vector3f _scale;
    Ptr<T> _pRendererObject;

};