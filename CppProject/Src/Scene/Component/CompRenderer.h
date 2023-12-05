#pragma once

#include "Component.h"
#include "IComponentType.h"
#include "Renderer/Buffer/InputAssemble.h"
#include "Renderer/Material/Material.h"

class CompRenderer: public Component, public IComponentType<ComponentType::Renderer>
{
public:
    CompRenderer(const Ptr<Renderer::InputAssemble>& pInputAssemble, const Ptr<Renderer::Material>& pMaterial);

public:
    const Ptr<Renderer::InputAssemble>& GetInputAssemble() const;
    void ChangeMaterial(const Ptr<Renderer::Material>& pNewMat);
    const Ptr<Renderer::Material>& GetMaterial() const;

protected:
    Ptr<Renderer::InputAssemble> _pInputAssemble;
    Ptr<Renderer::Material> _pMaterial;

};