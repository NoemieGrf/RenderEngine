#include "Model.h"
#include "tinyobjloader/tiny_obj_loader.h"
#include "Util/Logger/Logger.h"

namespace Renderer
{
    void Model::Load(const std::string& path)
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

        const auto& attrib = reader.GetAttrib();
        const auto& shapes = reader.GetShapes();

        struct UniqueVertex
        {
            int vertexIndex;
            int normalIndex;
            int texIndex;

            bool operator==(const UniqueVertex& other) const
            {
                return vertexIndex == other.vertexIndex
                       && normalIndex == other.normalIndex
                       && texIndex == other.texIndex;
            }
        };

        struct UniqueVertexHash
        {
            size_t operator() (const UniqueVertex& data) const
            {
                return std::hash<int>()(data.vertexIndex)
                       ^ std::hash<int>()(data.normalIndex)
                       ^ std::hash<int>()(data.texIndex);
            }
        };

        std::vector<UniqueVertex> _vertexData;
        std::vector<float> _vertexBufferData;
        std::vector<int> _indexData;
        std::unordered_map<UniqueVertex, int, UniqueVertexHash> _vertexToIndexMap;

        // for each single shape
        for (const auto& singleShape: shapes)
        {
            singleShape.name;
            const auto& singleShapeMesh = singleShape.mesh;

            size_t indexOffset = 0;

            // for each face
            for (auto vertexNum: singleShapeMesh.num_face_vertices)
            {
                // for each vertex
                for (size_t i = 0; i < vertexNum; i++)
                {
                    tinyobj::index_t index = singleShapeMesh.indices[indexOffset + i];

                    UniqueVertex uniqueVertex { index.vertex_index, index.normal_index, index.vertex_index };

                    // same vertex already exists, add index to index buffer, no more vertex data
                    if (_vertexToIndexMap.contains(uniqueVertex))
                    {
                        _indexData.push_back(_vertexToIndexMap[uniqueVertex]);
                    }
                    else
                    {
                        _vertexData.push_back(uniqueVertex);
                        _vertexToIndexMap[uniqueVertex] = _vertexData.size();
                    }




                    std::array<float, 8> vertexData { 0 };

                    // vertex
                    vertexData[0] = attrib.vertices[3 * index.vertex_index + 0];
                    vertexData[1] = attrib.vertices[3 * index.vertex_index + 1];
                    vertexData[2] = attrib.vertices[3 * index.vertex_index + 2];

                    // normal (if `normal_index` is zero or positive. negative = no normal data)
                    if (index.normal_index >= 0)
                    {
                        vertexData[3] = attrib.normals[3 * index.normal_index + 0];
                        vertexData[4] = attrib.normals[3 * index.normal_index + 1];
                        vertexData[5] = attrib.normals[3 * index.normal_index + 2];
                    }

                    // tex coord (if `texcoord_index` is zero or positive. negative = no tex coord data)
                    if (index.texcoord_index >= 0)
                    {
                        vertexData[6] = attrib.texcoords[2 * index.texcoord_index + 0];
                        vertexData[7] = attrib.texcoords[2 * index.texcoord_index + 1];
                    }

                    indexOffset += vertexNum;
                }
            }
        }
    }
}

