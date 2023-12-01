#pragma once

#include "Define/Define.h"
#include "Util/Logger/Logger.h"
#include "Util/NonConstructible.h"
#include "Util/NonCopyable.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderType.h"
#include "SpecificShader/VertexShader.h"
#include "SpecificShader/PixelShader.h"

#include <fstream>

namespace Renderer
{
    template<ShaderType shaderType>
    class ShaderPool: public NonConstructible
    {
    public:
        static Ptr<Shader> GetShader(const std::string& path)
        {
            auto findResult = _shaderPool.find(path);
            if (findResult != _shaderPool.end())
                return findResult->second;

            std::ifstream fs(path, std::ios::in | std::ios::binary);
            if (fs.is_open())
            {
                std::string content;

                fs.seekg(0, std::ios::end);
                unsigned int size = fs.tellg();
                content.resize(size);

                fs.seekg(0, std::ios::beg);
                fs.read(&content[0], size);

                fs.close();

                Ptr<Shader> pShader;
                if constexpr (shaderType == ShaderType::Vertex)
                    pShader = VertexShader::Create();
                else if constexpr (shaderType == ShaderType::Pixel)
                    pShader = PixelShader::Create();
                else
                    pShader = nullptr;

                if (pShader != nullptr)
                {
                    pShader->LoadFromString(content.c_str());
                    _shaderPool[path] = pShader;
                }

                return pShader;
            }
            else
            {
                Util::Logger::LogError("Get shader fail: {}", path);
                return nullptr;
            }
        }

        static void DeleteShader(const std::string& path)
        {
            auto findResult = _shaderPool.find(path);
            if (findResult != _shaderPool.end())
                _shaderPool.erase(findResult);
        }

    private:
        inline static umap<std::string, Ptr<Shader>> _shaderPool;
    };
}