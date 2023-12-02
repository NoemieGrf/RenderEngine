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

    void Texture2dOpenGL::Bind(unsigned int slot)
    {
        ::glBindTextureUnit(slot, _texturedId);
    }

    void Texture2dOpenGL::PushData(const Ptr<const Image>& pImage)
    {
        int imageChannel = pImage->GetChannels();

        GLenum storeChannel = GL_RGB8;
        GLenum submitChannel = GL_RGB;
        switch (imageChannel)
        {
            case 3:
                storeChannel = GL_RGB8;
                submitChannel = GL_RGB;
                break;
            case 4:
                storeChannel = GL_RGBA8;
                storeChannel = GL_RGBA;
                break;
        }

        auto size = pImage->GetSize();

        ::glActiveTexture(GL_TEXTURE0);
        Bind(0);
        ::glTextureStorage2D(_texturedId, 1, storeChannel, size.width, size.height);

        ::glTextureParameteri(_texturedId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        ::glTextureParameteri(_texturedId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        ::glTextureSubImage2D(_texturedId, 0, 0, 0, size.width, size.height, submitChannel, GL_UNSIGNED_BYTE, pImage->GetData());
    }
}