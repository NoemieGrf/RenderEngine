#pragma once

#include "UniformVariable.h"
#include "Renderer/Texture/Texture2d.h"

namespace Renderer
{
    class UniformVariableTexture2d: public UniformVariable
    {
    public:
        UniformVariableTexture2d(const std::string& name, const std::string& texPath, int texSlot);

    public:
        void Bind() override;
        UniformVariableType GetType() override;
        void SetUniform(Ptr<ShaderProgram>& pShader) override;

    private:
        int _slot;
        std::string _name;
        Ptr<Texture2d> _pTexture;
    };
}