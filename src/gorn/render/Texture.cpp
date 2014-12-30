#include <gorn/render/Texture.hpp>
#include <gorn/render/Image.hpp>

namespace gorn
{
	Texture::Texture(const Image& img, GLenum target, GLint lodLevel):
	_id(0)
	{
		glGenTextures(1, &_id);
        glBindTexture(target, _id);
        glTexImage2D(target, lodLevel, img.getInternalFormat(),
            img.getWidth(), img.getHeight(), img.getBorder(),
            img.getFormat(), img.getType(), img.getData().data());
	}

	Texture::~Texture()
	{
		if(_id != 0)
		{
			glDeleteTextures(1, &_id);
		}
	}

	GLuint Texture::getId() const
	{
		return _id;
	}
}