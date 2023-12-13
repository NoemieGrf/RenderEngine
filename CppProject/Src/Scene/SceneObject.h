#pragma once

#include <eigen/Eigen>
#include "Define/Define.h"
#include "Scene/Component/Component.h"
#include "Scene/Component/ComponentType.h"

class SceneObject
{
public:
    // name
    const std::string& GetName() const;
    void SetName(const std::string& name);

    // relation
    void AddChild(const Ptr<SceneObject>& pChild);
    const uset<Ptr<SceneObject>>& GetAllChildren();

    // transform
    const Eigen::Vector3f& GetLocalPosition() const;
    Eigen::Vector3f GetWorldPosition() const;
    const Eigen::Quaternionf& GetLocalRotation() const;
    Eigen::Quaternionf GetWorldRotation() const;
    const Eigen::Vector3f& GetLocalScale() const;
    Eigen::Vector3f GetWorldScale() const;
    const Eigen::Matrix4f& GetModelMatrix();

    void SetPosition(const Eigen::Vector3f& position);
    void SetRotation(const Eigen::Quaternionf& rotation);
    void SetScale(const Eigen::Vector3f& scale);

    template<class T, class... Types>
    void AddComponent(Types&&... Args);

    template<class T>
    Ptr<T> GetComponent();

private:
    void OnParentPositionChanged();
    void OnParentRotationChanged();
    void OnParentScaleChanged();

private:
    // name
    std::string _name;

    // relation
    Ptr<SceneObject> _parentObject = nullptr;
    uset<Ptr<SceneObject>> _childrenObjects;

    // transform
    Eigen::Vector3f _position = Eigen::Vector3f::Zero();
    Eigen::Quaternionf _rotation = Eigen::Quaternionf::Identity();
    Eigen::Vector3f _scale = Eigen::Vector3f::Ones();

    // model matrix
    bool _needUpdateModelMatrix = true;
    Eigen::Matrix4f _modelMatrix = Eigen::Matrix4f::Identity();

    // component map
    umap<ComponentType, Ptr<Component>> _componentMap;
};

template<class T, class... Types>
void SceneObject::AddComponent(Types&&... Args)
{
    ComponentType t = T::GetType();
    Ptr<Component> pComp = DynamicCast<Component>(std::make_shared<T>(std::forward<Types&&>(Args)...));
    pComp->SetSceneObject(this);
    pComp->OnPositionSet();
    pComp->OnRotationSet();
    pComp->OnScaleSet();
    _componentMap[t] = pComp;
}

template<class T>
Ptr<T> SceneObject::GetComponent()
{
    ComponentType t = T::GetType();
    return DynamicCast<T>(_componentMap[t]);
}