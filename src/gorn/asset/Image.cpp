#include <gorn/asset/Image.hpp>

namespace gorn
{
	Image::Image(Data&& data, const glm::vec2& size,
        bool hasAlpha, BasicType type, Format format) NOEXCEPT:
	_data(std::move(data)), _size(size), _hasAlpha(hasAlpha),
    _type(type), _format(format)
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

    const Data& Image::getData() const NOEXCEPT
    {
    	return _data;
    }
}
