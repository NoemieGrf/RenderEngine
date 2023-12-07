#include "Mesh.h"
#include "tinyobjloader/tiny_obj_loader.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{

    void Mesh::Load(const std::string& path)
    {
        tinyobj::ObjReaderConfig readerConfig;
        readerConfig.mtl_search_path = "./";

        tinyobj::ObjReader reader;

        bool readSuccess = reader.ParseFromFile(path, readerConfig);
        if (!readSuccess)
        {
            if (!reader.Error().empty())
                Util::Logger::LogError("Load obj fail at `{}`, error message = {}", path, reader.Error());
            else
                Util::Logger::LogError("Load obj fail at `{}`, error message = unknown", path);

            return;
        }

        if (!reader.Warning().empty())
            Util::Logger::LogWarn("Load obj at `{}`: {}", path, reader.Warning());

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& material = reader.GetMaterials();
    }
}