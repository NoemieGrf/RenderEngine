#include "InputAssembleOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"
#include "RendererHardwareInterface/OpenGL/Helper/OpenGLHelper.h"

namespace Renderer
{

    InputAssembleOpenGL::InputAssembleOpenGL()
    {
        ::glCreateVertexArrays(1, &_vertexArrayId);
    }

    InputAssembleOpenGL::~InputAssembleOpenGL()
    {
        ::glDeleteVertexArrays(1, &_vertexArrayId);
    }

    void InputAssembleOpenGL::Bind()
    {
        ::glBindVertexArray(_vertexArrayId);
    }

    void InputAssembleOpenGL::UnBind()
    {
        ::glBindVertexArray(0);
    }

    void InputAssembleOpenGL::AddVertexBuffer(const Ptr<const VertexBuffer>& pVertexBuffer)
    {
        if (pVertexBuffer == nullptr)
            return;

        ::glBindVertexArray(_vertexArrayId);
        pVertexBuffer->Bind();

        unsigned int index = 0;
        auto vertexBufferLayout = pVertexBuffer->GetLayout();
        for (const auto& element : vertexBufferLayout.GetLayout())
        {
            auto dataCount = ShaderDataTypeHelper::GetShaderDataCount(element.dataType);
            GLenum glEnum = OpenGLHelper::GetShaderDataTypeGlEnum(element.dataType);
            bool normalized = element.normalized ? GL_TRUE : GL_FALSE;
            auto stride = vertexBufferLayout.GetStride();
            auto offset = element.offset;

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, dataCount, glEnum, normalized, stride, reinterpret_cast<const void*>(offset));

            index++;
        }

        _vertexBufferVec.push_back(pVertexBuffer);
    }

    void InputAssembleOpenGL::SetIndexBuffer(const Ptr<const IndexBuffer>& pIndexBuffer)
    {
        if (pIndexBuffer == nullptr)
            return;

        ::glBindVertexArray(_vertexArrayId);
        pIndexBuffer->Bind();

        _pCurrentIndexBuffer = pIndexBuffer;
    }

    const std::vector<Ptr<const VertexBuffer>>& InputAssembleOpenGL::GetVertexBufferVector() const
    {
        return _vertexBufferVec;
    }

    Ptr<const IndexBuffer> InputAssembleOpenGL::GetCurrentIndexBuffer() const
    {
        return _pCurrentIndexBuffer;
    }
}