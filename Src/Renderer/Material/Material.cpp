#include "Material.h"
#include <fstream>
#include <functional>
#include "nlohmann/json.hpp"
#include "Renderer/Shader/ShaderType.h"
#include "UniformVariable/UniformVariableType.h"
#include "Util/Logger/Logger.h"
#include "Renderer/Material/UniformVariable/UniformVariableTexture2d.h"
#include "Renderer/Material/UniformVariable/UniformVariableNumeric.h"

namespace Renderer
{
    class MaterialJsonHelper
    {
    public:
        static void ParseUniformVar(const nlohmann::basic_json<>& node, std::function<void(const Ptr<UniformVariable>&)> onUniVarCreate)
        {
            if (node.contains("Uniform") && node["Uniform"].is_array())
            {
                for (const auto& uniformVarConfig: node["Uniform"])
                {
                    Ptr<UniformVariable> pUniVar = CreateUniformVar(uniformVarConfig);
                    onUniVarCreate(pUniVar);
                }
            }
        }

        static Ptr<UniformVariable> CreateUniformVar(const nlohmann::basic_json<>& uniformVarConfig)
        {
            Ptr<UniformVariable> pUniVar = nullptr;

            const std::string& uniVarType = uniformVarConfig["Type"];
            const std::string& uniVarName = uniformVarConfig["Name"];
            if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Texture2D))
            {
                const std::string& texPath = uniformVarConfig["Path"];
                int slot = uniformVarConfig["Slot"];
                pUniVar = std::make_shared<UniformVariableTexture2d>(uniVarName, texPath, slot);
            }
            else if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Int))
            {
                int value = uniformVarConfig["Value"];
                pUniVar = std::make_shared<UniformVariableNumeric<int>>(uniVarName, value);
            }
            else if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Uint))
            {
                unsigned int value = uniformVarConfig["Value"];
                pUniVar = std::make_shared<UniformVariableNumeric<unsigned int>>(uniVarName, value);
            }
            else if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Float))
            {
                float value = uniformVarConfig["Value"];
                pUniVar = std::make_shared<UniformVariableNumeric<float>>(uniVarName, value);
            }
            else if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Float2))
            {
                const float x = uniformVarConfig["X"];
                const float y = uniformVarConfig["Y"];
                pUniVar = std::make_shared<UniformVariableNumeric<Eigen::Vector2f>>(uniVarName, Eigen::Vector2f { x, y });
            }
            else if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Float3))
            {
                const float x = uniformVarConfig["X"];
                const float y = uniformVarConfig["Y"];
                const float z = uniformVarConfig["Z"];
                pUniVar = std::make_shared<UniformVariableNumeric<Eigen::Vector3f>>(uniVarName, Eigen::Vector3f { x, y, z });
            }
            else if (uniVarType == UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType::Float4))
            {
                const float x = uniformVarConfig["X"];
                const float y = uniformVarConfig["Y"];
                const float z = uniformVarConfig["Z"];
                const float w = uniformVarConfig["W"];
                pUniVar = std::make_shared<UniformVariableNumeric<Eigen::Vector4f>>(uniVarName, Eigen::Vector4f { x, y, z, w });
            }

            return pUniVar;
        }
    };

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

            // uniform create callback
            std::function<void(const Ptr<UniformVariable>&)> onUniVarCreate = [this, &pass](const Ptr<UniformVariable>& pUniVar)
            {
                if (pUniVar != nullptr)
                    _passUniVars[pass.value()].push_back(pUniVar);
            };

            // vertex
            const std::string& vertexShaderTypeName = ShaderTypeHelper::ShaderTypeToString(ShaderType::Vertex);
            if (passShaderConfig.contains(vertexShaderTypeName))
            {
                auto vertexNode = passShaderConfig[vertexShaderTypeName];
                const std::string& shaderPath = vertexNode["Path"];
                pShader->AddShader<ShaderType::Vertex>(shaderPath);

                // uniform
                MaterialJsonHelper::ParseUniformVar(vertexNode, onUniVarCreate);
            }

            // pixel
            const std::string& pixelShaderTypeName = ShaderTypeHelper::ShaderTypeToString(ShaderType::Pixel);
            if (passShaderConfig.contains(pixelShaderTypeName))
            {
                // attach shader
                auto pixelNode = passShaderConfig[pixelShaderTypeName];
                const std::string shaderPath = pixelNode["Path"];
                pShader->AddShader<ShaderType::Pixel>(shaderPath);

                // uniform
                MaterialJsonHelper::ParseUniformVar(pixelNode, onUniVarCreate);
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