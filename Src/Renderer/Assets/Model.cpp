#include <cassert>
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

        for (int shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++)
        {
            // May not mesh
            if (shapes[shapeIndex].mesh.indices.empty())
                continue;

            // Create mesh
            std::string meshName = shapes[shapeIndex].name;
            if (meshName.empty())
                meshName = std::to_string(shapeIndex);

            Ptr<Mesh> pMesh = std::make_shared<Mesh>();
            _meshMap[meshName] = pMesh;

            // Prepare
            const auto& singleMeshData = shapes[shapeIndex].mesh;
            std::vector<UniqueVertex> _vertexData;
            std::unordered_map<UniqueVertex, int, UniqueVertexHash> _vertexToIndexMap;
            pMesh->_vertexData.clear();
            pMesh->_indexData.clear();
            size_t indexOffset = 0;

            // Check layout
            const auto& firstFaceFirstVertex = singleMeshData.indices[0];
            bool meshHasNormal = firstFaceFirstVertex.normal_index >= 0;
            bool meshHasTexCoord = firstFaceFirstVertex.texcoord_index >= 0;
            pMesh->_dataLayout = InputLayout({
                    InputLayoutElement{ Renderer::ShaderDataType::Float3, "a_Position" },
                    InputLayoutElement{ Renderer::ShaderDataType::Float3, "a_Normal" },
                    InputLayoutElement{ Renderer::ShaderDataType::Float2, "a_TexCoord" }
            });

            // For each face
            for (auto faceVertexNum: singleMeshData.num_face_vertices)
            {
                // For each face vertex
                for (size_t i = 0; i < faceVertexNum; i++)
                {
                    tinyobj::index_t index = singleMeshData.indices[indexOffset + i];

                    UniqueVertex uniqueVertex { index.vertex_index, index.normal_index, index.vertex_index };

                    // Same vertex already exists, add index to index buffer, no more vertex data
                    if (_vertexToIndexMap.contains(uniqueVertex))
                    {
                        pMesh->_indexData.push_back(_vertexToIndexMap[uniqueVertex]);
                        continue;
                    }

                    _vertexToIndexMap[uniqueVertex] = _vertexData.size();
                    _vertexData.push_back(uniqueVertex);
                    pMesh->_indexData.push_back(_vertexToIndexMap[uniqueVertex]);

                    // Add vertex data
                    pMesh->_vertexData.push_back(attrib.vertices[3 * index.vertex_index + 0]);
                    pMesh->_vertexData.push_back(attrib.vertices[3 * index.vertex_index + 1]);
                    pMesh->_vertexData.push_back(attrib.vertices[3 * index.vertex_index + 2]);

                    // Add normal data
                    if (meshHasNormal && index.normal_index >= 0)
                    {
                        pMesh->_vertexData.push_back(attrib.normals[3 * index.normal_index + 0]);
                        pMesh->_vertexData.push_back(attrib.normals[3 * index.normal_index + 1]);
                        pMesh->_vertexData.push_back(attrib.normals[3 * index.normal_index + 2]);
                    }
                    else
                    {
                        pMesh->_vertexData.push_back(0);
                        pMesh->_vertexData.push_back(0);
                        pMesh->_vertexData.push_back(0);
                    }

                    // Add tex coord
                    if (meshHasTexCoord && index.texcoord_index >= 0)
                    {
                        pMesh->_vertexData.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                        pMesh->_vertexData.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
                    }
                    else
                    {
                        pMesh->_vertexData.push_back(0);
                        pMesh->_vertexData.push_back(0);
                    }
                }

                indexOffset += faceVertexNum;
            }

            // Mesh load finish
            assert(pMesh->_vertexData.size() * sizeof(float) == _vertexData.size() * pMesh->_dataLayout.GetStride());
        }
    }
    const std::unordered_map<std::string, Ptr<Mesh>>& Model::GetMeshMap() const
    {
        return _meshMap;
    }

    Ptr<Model> Model::Create(const std::string& path)
    {
        Ptr<Model> pModel = std::make_shared<Model>();
        pModel->Load(path);
        return pModel;
    }
}

