#include <gorn/asset/Image.hpp>
#include <utility>

namespace gorn
{
    Image::Image(buffer&& data, const glm::vec2& size,
        bool hasAlpha, BasicType type, Format format) NOEXCEPT:
    _data(std::move(data)), _size(size), _hasAlpha(hasAlpha),
    _type(type), _format(format)
    {
    }

    Image::Image(buffer&& data, DataOrigin origin, const glm::vec2& size,
    bool hasAlpha, BasicType type, Format format) NOEXCEPT:
    _data(std::move(data)), _size(size), _hasAlpha(hasAlpha),
    _type(type), _format(format)
    {
        if(origin == DataOrigin::TopLeft)
        {
            flipDataVertically();
        }
    }

    Image::Image(const glm::vec2& size, bool hasAlpha,
            BasicType type) NOEXCEPT:
    _size(size), _hasAlpha(hasAlpha),
    _type(type), _format(Format::Uncompressed)
    {
    }

    const glm::vec2& Image::getSize() const NOEXCEPT
    {
        return _size;
    }

    Image::Format Image::getFormat() const NOEXCEPT
    {
        return _format;
    }

    BasicType Image::getType() const NOEXCEPT
    {
        return _type;
    }

    bool Image::hasAlpha() const NOEXCEPT
    {
        return _hasAlpha;
    }

    const buffer& Image::getData() const NOEXCEPT
    {
        return _data;
    }

    void Image::flipDataVertically()
    {
        size_t h = (size_t)_size.y;
        size_t c = _data.size()/h;
        for(size_t y=0; y<h/2; y++)
        {
            for(size_t x=0; x<c; x++)
            {
                size_t a = y*c+x;
                size_t b = (h-y-1)*c+x;
                uint8_t t = _data[a];
                _data[a] = _data[b];
                _data[b] = t;
            }
        }
    }
}
