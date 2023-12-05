#include "RendererPassForward.h"
#include "Scene/Scene.h"
#include "Scene/Component/CompCamera.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/RenderCommand/RenderCommand.h"

namespace Renderer
{
    void RendererPassForward::Init()
    {

    }

    void RendererPassForward::Renderer(const Scene* pScene)
    {
        auto pMainCamera = pScene->GetMainCamera()->GetComponent<CompCamera>()->GetCamera();
        for (const auto& pObj: pScene->GetAllObjects())
        {
            auto pRenderer = pObj->GetComponent<CompRenderer>();
            if (pRenderer == nullptr)
                continue;

            auto pAssemble = pRenderer->GetInputAssemble();
            auto pMat = pRenderer->GetMaterial();

            // General uniform
            pMat->GetShader(RendererPassType::Forward)->Bind();
            pMat->GetShader(RendererPassType::Forward)->SetUniformMat4("u_VPMatrix", pMainCamera->GetVPMatrix());

            // Draw Call
            Renderer::RenderCommand::Submit<RendererPassType::Forward>(pAssemble, pMat);
        }
    }
}