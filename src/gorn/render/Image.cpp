#include <gorn/render/Image.hpp>

namespace gorn
{
	Image::Image(Data&& data, GLsizei w, GLsizei h,
        GLenum format, GLenum type, GLint border, GLint internalFormat):
	_data(std::move(data)), _width(w), _height(h), _format(format), _type(type),
    _border(border), _internalFormat(internalFormat==0?format:internalFormat)
	{
	}

    GLsizei Image::getWidth() const
    {
    	return _width;
    }

    GLsizei Image::getHeight() const
    {
    	return _height;
    }

    GLenum Image::getFormat() const
    {
    	return _format;
    }

    GLenum Image::getType() const
    {
    	return _type;
    }

    GLint Image::getBorder() const
    {
        return _border;
    }

    GLint Image::getInternalFormat() const
    {
        return _internalFormat;
    }

    const Data& Image::getData() const
    {
    	return _data;
    }
}