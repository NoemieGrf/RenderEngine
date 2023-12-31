#include <cassert>

#include "Image.h"
#include "stb/stb_image.h"

namespace Renderer 
{
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

    Ptr<Image> Image::Create(const std::string& path)
    {
        Ptr<Image> pImage = std::make_shared<Image>();
        pImage->Load(path);
        return pImage;
    }

    void Image::Load(const std::string& path)
    {
        stbi_set_flip_vertically_on_load(true);
        auto pData = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
        _pData = reinterpret_cast<std::byte*>(pData);

        assert(_pData != nullptr);
    }
}