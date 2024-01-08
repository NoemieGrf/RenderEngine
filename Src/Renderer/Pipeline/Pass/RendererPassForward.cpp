#include "RendererPassForward.h"
#include "Scene/Scene.h"
#include "Scene/Component/CompCamera.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/RenderCommand/RenderCommand.h"

namespace Renderer
{
    void RendererPassForward::Init()
    {
        Ptr<UniformBlock> pUniBlockMvp = UniformBlock::Create("MvpMatrices");
        pUniBlockMvp->Set({
            { "u_ModelMatrix", ShaderDataType::Matrix4x4 },
            { "u_ViewMatrix", ShaderDataType::Matrix4x4 },
            { "u_ProjectionMatrix", ShaderDataType::Matrix4x4 },
        });

        Ptr<UniformBuffer> pUniBuffer = UniformBuffer::Create();

    }

    void RendererPassForward::Renderer(const Scene* pScene)
    {
        auto pMainCamera = pScene->GetMainCamera()->GetComponent<CompCamera>();
        for (const auto& pObj: pScene->GetAllObjects())
        {
            auto pRenderer = pObj->GetComponent<CompRenderer>();
            if (pRenderer == nullptr)
                continue;

            auto pAssemble = pRenderer->GetInputAssemble();
            auto pMat = pRenderer->GetMaterial();

            // General uniform
            pMat->GetShader(RendererPassType::Forward)->Bind();
            pMat->GetShader(RendererPassType::Forward)->SetUniformMat4("u_ModelMatrix", pObj->GetModelMatrix());
            pMat->GetShader(RendererPassType::Forward)->SetUniformMat4("u_ViewMatrix", pMainCamera->GetViewMatrix());
            pMat->GetShader(RendererPassType::Forward)->SetUniformMat4("u_ProjectionMatrix",pMainCamera->GetProjectionMatrix());

            // Draw Call
            Renderer::RenderCommand::Submit<RendererPassType::Forward>(pAssemble, pMat);
        }
    }
}