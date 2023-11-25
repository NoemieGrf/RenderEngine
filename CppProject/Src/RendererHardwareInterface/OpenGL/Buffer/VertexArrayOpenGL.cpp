#include "VertexArrayOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Helper/OpenGLHelper.h"

namespace Renderer
{

    VertexArrayOpenGL::VertexArrayOpenGL()
    {
        ::glCreateVertexArrays(1, &_vertexArrayId);
    }

    VertexArrayOpenGL::~VertexArrayOpenGL()
    {
        ::glDeleteVertexArrays(1, &_vertexArrayId);
    }

    void VertexArrayOpenGL::Bind()
    {
        ::glBindVertexArray(_vertexArrayId);
    }

    void VertexArrayOpenGL::UnBind()
    {
        ::glBindVertexArray(0);
    }

    void VertexArrayOpenGL::AddVertexBuffer(const Ptr<const VertexBuffer>& pVertexBuffer)
    {
        if (pVertexBuffer == nullptr)
            return;

        ::glBindVertexArray(_vertexArrayId);
        pVertexBuffer->Bind();

        unsigned int index = 0;
        auto vertexBufferLayout = pVertexBuffer->GetLayout();
        for (const auto& element : vertexBufferLayout.GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  ShaderDataTypeHelper::GetShaderDataCount(element.dataType),
                                  OpenGLHelper::GetShaderDataTypeGlEnum(element.dataType),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  vertexBufferLayout.GetStride(),
                                  reinterpret_cast<const void*>(element.offset));

            index++;
        }

        _vertexBufferVec.push_back(pVertexBuffer);
    }

    void VertexArrayOpenGL::SetIndexBuffer(const Ptr<const IndexBuffer>& pIndexBuffer)
    {
        if (pIndexBuffer == nullptr)
            return;

        ::glBindVertexArray(_vertexArrayId);
        pIndexBuffer->Bind();

        _pCurrentIndexBuffer = pIndexBuffer;
    }

    const std::vector<Ptr<const VertexBuffer>>& VertexArrayOpenGL::GetVertexBufferVector() const
    {
        return _vertexBufferVec;
    }

    Ptr<const IndexBuffer> VertexArrayOpenGL::GetCurrentIndexBuffer() const
    {
        return _pCurrentIndexBuffer;
    }
}