#include "UniformVariableTexture2d.h"
#include "Renderer/Assets/Image.h"

namespace Renderer
{
    UniformVariableTexture2d::UniformVariableTexture2d(const std::string& name, const std::string& texPath, int texSlot)
        : _name(name)
        , _pTexture(Texture2d::Create())
        , _slot(texSlot)
    {
        Ptr<Image> pImage = std::make_shared<Image>(texPath);
        _pTexture->PushData(pImage);
    }

    UniformVariableType UniformVariableTexture2d::GetType()
    {
        return UniformVariableType::Texture2D;
    }

    void UniformVariableTexture2d::Bind()
    {
        _pTexture->Bind(_slot);
    }

    void UniformVariableTexture2d::SetUniform(Ptr<ShaderProgram>& pShader)
    {
        assert(_pTexture != nullptr);
        pShader->SetUniformUnsignedInt(_name, _slot);
    }

}