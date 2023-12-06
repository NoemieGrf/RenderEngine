#pragma once

#include <eigen/Eigen>
#include <unordered_map>
#include "Define/Define.h"
#include "Scene/Component/Component.h"
#include "Scene/Component/ComponentType.h"

class SceneObject
{
public:
    const Eigen::Vector3f& GetPosition() const;
    const Eigen::Quaternionf& GetRotation() const;
    const Eigen::Vector3f& GetScale() const;
    const Eigen::Matrix4f& GetModelMatrix();

    void SetPosition(const Eigen::Vector3f& position);
    void SetRotation(const Eigen::Quaternionf& rotation);
    void SetScale(const Eigen::Vector3f& scale);

    template<class T, class... Types>
    void AddComponent(Types&&... Args)
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
    Ptr<T> GetComponent()
    {
        ComponentType t = T::GetType();
        return DynamicCast<T>(_componentMap[t]);
    }

private:
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