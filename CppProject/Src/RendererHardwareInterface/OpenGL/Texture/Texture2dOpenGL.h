#pragma once

#include "Renderer/Texture/Texture2d.h"

namespace Renderer 
{
    class Texture2dOpenGL: public Texture2d
    {
    public:
        Texture2dOpenGL();
        ~Texture2dOpenGL() override;
        void Bind() override;
        void PushData(const Ptr<const Image>& pImage) override;

    private:
        unsigned int _texturedId = 0;
    };
}