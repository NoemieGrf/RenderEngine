#include "CompRenderer.h"

CompRenderer::CompRenderer(const Ptr<Renderer::InputAssemble>& pInputAssemble, const Ptr<Renderer::Material>& pMaterial)
    : _pInputAssemble(pInputAssemble)
    , _pMaterial(pMaterial)
{

}

const Ptr<Renderer::InputAssemble>& CompRenderer::GetInputAssemble() const
{
    return _pInputAssemble;
}

const Ptr<Renderer::Material>& CompRenderer::GetMaterial() const
{
    return _pMaterial;
}
