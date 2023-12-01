#pragma once

#include "Renderer/Assets/Image.h"
#include "Define/Define.h"

namespace Renderer 
{
    class Texture2d
    {
    public:
        virtual ~Texture2d() = default;

    public:
        virtual void Bind() = 0;
        virtual void PushData(const Ptr<const Image>& pImage) = 0;

    public:
        static Ptr<Texture2d> Create();

    };
}