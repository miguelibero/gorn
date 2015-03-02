#include <gorn/asset/Image.hpp>

namespace gorn
{
	Image::Image(Data&& data, const glm::vec2& size,
        bool hasAlpha, BasicType type, Format format):
	_data(std::move(data)), _size(size), _hasAlpha(hasAlpha),
    _type(type), _format(format)
	{
	}

    const glm::vec2& Image::getSize() const
    {
    	return _size;
    }

    Image::Format Image::getFormat() const
    {
    	return _format;
    }

    BasicType Image::getType() const
    {
    	return _type;
    }

    bool Image::hasAlpha() const
    {
        return _hasAlpha;
    }

    const Data& Image::getData() const
    {
    	return _data;
    }
}
