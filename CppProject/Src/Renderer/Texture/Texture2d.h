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
        void SetSlot(unsigned int newSlot);
        unsigned int GetSlot() const;
        virtual void Bind() = 0;
        virtual void PushData(const Ptr<const Image>& pImage) = 0;

    protected:
        unsigned int _slot = 0;

    public:
        static Ptr<Texture2d> Create();

    };
}