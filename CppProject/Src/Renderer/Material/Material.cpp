#include <fstream>
#include "nlohmann/json.hpp"

#include "Material.h"
#include "Renderer/Shader/ShaderPool.hpp"
#include "Util/Logger/Logger.h"

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


    }
}