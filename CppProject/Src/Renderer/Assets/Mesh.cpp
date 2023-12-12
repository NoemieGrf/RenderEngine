
#include "Mesh.h"

namespace Renderer
{

    const std::vector<float>& Mesh::GetVertexData() const
    {
        return _vertexData;
    }

    const std::vector<unsigned int>& Mesh::GetIndexData() const
    {
        return _indexData;
    }

    const InputLayout& Mesh::GetLayout() const
    {
        return _dataLayout;
    }
}