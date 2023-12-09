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

        for (size_t s = 0; s < shapes.size(); s++)
        {
            size_t index_offset = 0;

            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                    // Check if `normal_index` is zero or positive. negative = no normal data
                    if (idx.normal_index >= 0)
                    {
                        tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                    if (idx.texcoord_index >= 0)
                    {
                        tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }
                }

                index_offset += fv;

                // per-face material
                shapes[s].mesh.material_ids[f];
            }
        }
    }
}