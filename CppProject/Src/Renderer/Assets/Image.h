#pragma once

#include <cstddef>
#include <string>
#include "Define/Define.h"

namespace Renderer 
{
    class Image
    {
    public:
        struct Size
        {
            int width;
            int height;
        };

    public:
        virtual ~Image();

    public:
        const std::byte* GetData() const;
        Size GetSize() const;
        int GetChannels() const;

        static Ptr<Image> Create(const std::string& path);

    private:
        void Load(const std::string& path);

    private:
        int _width = 0;
        int _height = 0;
        int _channels = 0;
        std::byte* _pData = nullptr;
    };
}