#include "Material.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "Renderer/Shader/ShaderType.h"
#include "UniformVariable/UniformVariableType.h"
#include "Util/Logger/Logger.h"
#include "Renderer/Material/UniformVariable/UniformVariableTexture2d.h"
#include "Renderer/Material/UniformVariable/UniformVariableNumeric.h"

namespace Renderer
{
    Material::Material(const std::string& materialPath)
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

        for (const auto& [passName, passShaderConfig]: json.items())
        {
            auto pass = RendererPassTypeHelper::StringToRendererPassType(passName);
            if (!pass.has_value())
            {
                Util::Logger::LogError("Material pass error, {}, {}", materialPath, passName);
                continue;
            }

            auto pShader = ShaderProgram::Create();

            // vertex
            std::string vertexShaderTypeName = ShaderTypeHelper::ShaderTypeToString(ShaderType::Vertex);
            if (passShaderConfig.contains(vertexShaderTypeName))
            {
                auto vertexNode = passShaderConfig[vertexShaderTypeName];
                const std::string& shaderPath = vertexNode["Path"];
                pShader->AddShader<ShaderType::Vertex>(shaderPath);
            }

            // pixel
            std::string pixelShaderTypeName = ShaderTypeHelper::ShaderTypeToString(ShaderType::Pixel);
            if (passShaderConfig.contains(pixelShaderTypeName))
            {
                // attach shader
                auto pixelNode = passShaderConfig[pixelShaderTypeName];
                const std::string shaderPath = pixelNode["Path"];
                pShader->AddShader<ShaderType::Pixel>(shaderPath);

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
                            _passUniVars[pass.value()].push_back(pUniVar);
                        }
                    }
                }
            }

            pShader->Compile();
            _passShaderMap[pass.value()] = pShader;
        }
    }

    void Material::Bind(RendererPassType pass)
    {
        if (_passShaderMap.contains(pass))
            _passShaderMap[pass]->Bind();

        if (_passUniVars.contains(pass))
        {
            for (const auto& pUni: _passUniVars[pass])
                pUni->Bind();
        }
    }

    void Material::SetUniform(RendererPassType pass)
    {
        if (!_passShaderMap.contains(pass) || !_passUniVars.contains(pass))
            return;

        auto& pPassShader = _passShaderMap[pass];
        for (const auto& pUni: _passUniVars[pass])
            pUni->SetUniform(pPassShader);
    }

    Ptr<ShaderProgram> Material::GetShader(RendererPassType pass) const
    {
        if (_passShaderMap.contains(pass))
            return _passShaderMap.at(pass);

        return nullptr;
    }

    const std::vector<Ptr<UniformVariable>>* Material::GetUniformVariables(RendererPassType pass) const
    {
        if (_passUniVars.contains(pass))
            return &_passUniVars.at(pass);

        return nullptr;
    }
}