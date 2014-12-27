#include <gorn/render/Image.hpp>

namespace gorn
{
	Image::Image(Data&& data, GLenum target, GLint level, GLint internalFormat,
		GLsizei w, GLsizei h, GLint border, GLenum format, GLenum type):
	_data(std::move(data)), _target(target), _level(level), _internalFormat(internalFormat),
	_width(w), _height(h), _border(border), _format(format), _type(type)
	{
	}

	GLenum Image::getTarget() const
	{
		return _target;
	}

    GLint Image::getLevel() const
    {
    	return _level;
    }

    GLint Image::getInternalFormat() const
    {
    	return _internalFormat;
    }

    GLsizei Image::getWidth() const
    {
    	return _width;
    }

    GLsizei Image::getHeight() const
    {
    	return _height;
    }

    GLint Image::getBorder() const
    {
    	return _border;
    }

    GLenum Image::getFormat() const
    {
    	return _format;
    }

    GLenum Image::getType() const
    {
    	return _type;
    }

    const GLvoid* Image::getData() const
    {
    	return _data.data();
    }
}