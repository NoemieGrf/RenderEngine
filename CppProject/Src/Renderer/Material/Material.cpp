#include "Material.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "Renderer/Shader/ShaderType.h"
#include "UniformVariable/UniformVariableType.h"
#include "Util/Logger/Logger.h"
#include "Renderer/Material/UniformVariable/UniformVariableTexture2d.h"

namespace Renderer
{
    Material::Material(const std::string& materialPath)
        : _pShader(ShaderProgram::Create())
    {
        std::ifstream fileStream(materialPath);
        if (!fileStream.is_open())
        {
            Util::Logger::LogError("Get material fail: {}", materialPath);
            return;
        }

        nlohmann::json json;
        fileStream >> json;
        fileStream.close();

        // vertex
        std::string vertexShaderTypeName = ShaderTypeHelper::ShaderTypeToString(ShaderType::Vertex);
        if (json.contains(vertexShaderTypeName))
        {
            auto vertexNode = json[vertexShaderTypeName];
            const std::string& shaderPath = vertexNode["Path"];
            _pShader->AddShader<ShaderType::Vertex>(shaderPath);
        }

        // pixel
        std::string pixelShaderTypeName = ShaderTypeHelper::ShaderTypeToString(ShaderType::Pixel);
        if (json.contains(pixelShaderTypeName))
        {
            // attach shader
            auto pixelNode = json[pixelShaderTypeName];
            const std::string shaderPath = pixelNode["Path"];
            _pShader->AddShader<ShaderType::Pixel>(shaderPath);

            // uniform
            if (pixelNode.contains("Uniform") && pixelNode["Uniform"].is_array())
            {
                for (const auto& uniformVarConfig: pixelNode["Uniform"])
                {
                    if (uniformVarConfig["Type"] == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Texture2D))
                    {
                        const std::string& name = uniformVarConfig["Name"];
                        const std::string& texPath = uniformVarConfig["Path"];
                        int slot = uniformVarConfig["Slot"];
                        Ptr<UniformVariable> pUniVar = std::make_shared<UniformVariableTexture2d>(name, texPath, slot);
                        _uniVars.push_back(pUniVar);
                    }
                }
            }
        }

        _pShader->Compile();
    }

    void Material::Bind()
    {
        _pShader->Bind();
        for (const auto& pUni: _uniVars)
            pUni->Bind();
    }

    void Material::SetUniform()
    {
        for (const auto& pUni: _uniVars)
            pUni->SetUniform(_pShader);
    }

    Ptr<ShaderProgram> Material::GetShader() const
    {
        return _pShader;
    }

    const std::vector<Ptr<UniformVariable>>& Material::GetUniformVariables() const
    {
        return _uniVars;
    }
}