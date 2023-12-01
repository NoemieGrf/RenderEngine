#pragma once

#include <string>
#include <cstddef>

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
        explicit Image(const std::string& path);
        virtual ~Image();

    public:
        const std::byte* GetData() const;
        Size GetSize() const;
        int GetChannels() const;

    private:
        int _width = 0;
        int _height = 0;
        int _channels = 0;
        std::byte* _pData = nullptr;
    };
}