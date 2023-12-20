#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "UniformVariable/UniformVariable.h"
#include "Renderer/Pipeline/Pass/RendererPassType.h"

namespace Renderer
{
    class Material
    {
    public:
        explicit Material(const std::string& materialPath);

    public:
        void Bind(RendererPassType pass);
        void SetUniform(RendererPassType pass);
        Ptr<ShaderProgram> GetShader(RendererPassType pass) const;
        const std::vector<Ptr<UniformVariable>>* GetUniformVariables(RendererPassType pass) const;

    private:
        umap<RendererPassType, Ptr<ShaderProgram>> _passShaderMap;
        umap<RendererPassType, std::vector<Ptr<UniformVariable>>> _passUniVars;
    };
}