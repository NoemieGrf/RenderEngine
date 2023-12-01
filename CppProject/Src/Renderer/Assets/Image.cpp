#include <cassert>

#include "Image.h"
#include "stb/stb_image.h"

namespace Renderer 
{
    Image::Image(const std::string& path)
    {
        int width;
        int height;
        int channels;
        auto pData = stbi_load(path.c_str(), &width, &height, &channels, 0);
        _pData = reinterpret_cast<std::byte*>(pData);

        assert(_pData != nullptr);
    }

    Image::~Image()
    {
        if (_pData != nullptr)
            stbi_image_free(_pData);
    }

    const std::byte* Image::GetData() const
    {
        return _pData;
    }

    Image::Size Image::GetSize() const
    {
        return { _width, _height };
    } 

    int Image::GetChannels() const
    {
        return _channels;
    }
}