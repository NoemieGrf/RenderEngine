#pragma once

#include "Define/Define.h"
#include "Util/Logger/Logger.h"
#include "Util/NonConstructible.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderType.h"

#include <fstream>

namespace Renderer
{
    template <ShaderType T>
    class ShaderPool: public NonConstructible
    {
        using SpecificShader = TypeShader<T>;

    public:
        static Ptr<SpecificShader> GetShader(const std::string& path)
        {
            auto findResult = _shaderPool.find(path);
            if (findResult != _shaderPool.end())
                return *findResult;

            std::ifstream fs(path, std::ios::in, std::ios::binary);
            if (!fs.is_open())
            {
                std::string content;

                fs.seekg(0, std::ios::end);
                unsigned int size = fs.tellg();
                content.resize(size);

                fs.seekg(0, std::ios::beg);
                fs.read(&content[0], size);

                fs.close();

                Ptr<SpecificShader> pShader = SpecificShader::Create();
                _shaderPool[path] = pShader;

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
        inline static umap<std::string, Ptr<SpecificShader>> _shaderPool;
    };
}