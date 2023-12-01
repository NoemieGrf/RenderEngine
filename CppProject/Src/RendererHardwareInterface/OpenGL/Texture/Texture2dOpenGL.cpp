#include "Texture2dOpenGL.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"

namespace Renderer 
{
    Texture2dOpenGL::Texture2dOpenGL()
    {
        ::glGenTextures(1, &_texturedId);
    }

    Texture2dOpenGL::~Texture2dOpenGL()
    {
        ::glDeleteTextures(1, &_texturedId);
    }

    void Texture2dOpenGL::Bind()
    {
        ::glBindTexture(GL_TEXTURE_2D, _texturedId);
    }

    void Texture2dOpenGL::PushData(const Ptr<const Image>& pImage)
    {
        GLenum channel = GL_RGBA;
        switch (pImage->GetChannels()) 
        {
            case 3:
                channel = GL_RGB8;
                break;
            case 4:
                channel = GL_RGBA8;
                break;
        }

        auto size = pImage->GetSize();
        ::glTextureStorage2D(_texturedId, 1, channel, size.width, size.height);
        ::glTextureSubImage2D(_texturedId, 0, 0, 0, size.width, size.height, channel, GL_UNSIGNED_BYTE, pImage->GetData());
    }
}