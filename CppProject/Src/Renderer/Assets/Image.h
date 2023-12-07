#pragma once

#include <string>
#include <cstddef>
#include "AssetsPool.hpp"

namespace Renderer 
{
    class Image
    {
    public:
        friend class AssetsPool<Image>;

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

    private:
        void Load(const std::string& path);

    private:
        int _width = 0;
        int _height = 0;
        int _channels = 0;
        std::byte* _pData = nullptr;
    };
}