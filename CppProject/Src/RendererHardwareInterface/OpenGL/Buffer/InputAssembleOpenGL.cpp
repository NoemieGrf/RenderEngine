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
        _pVertexBuffer->Bind();
        _pIndexBuffer->Bind();

        unsigned int index = 0;
        for (const auto& element : _inputLayout.GetLayout())
        {
            auto dataCount = ShaderDataTypeHelper::GetShaderDataCount(element.dataType);
            GLenum glEnum = OpenGLHelper::GetShaderDataTypeGlEnum(element.dataType);
            bool normalized = element.normalized ? GL_TRUE : GL_FALSE;
            auto stride = _inputLayout.GetStride();
            auto offset = element.offset;

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, dataCount, glEnum, normalized, stride, reinterpret_cast<const void*>(offset));

            index++;
        }
    }

    void InputAssembleOpenGL::UnBind()
    {
        ::glBindVertexArray(0);
    }
}