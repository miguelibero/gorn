#include <gorn/render/Texture.hpp>
#include <gorn/render/Image.hpp>

namespace gorn
{
	Texture::Texture(const Image& img, GLenum target, GLint lodLevel):
	_id(0), _target(target)
	{
		glGenTextures(1, &_id);
        setImage(img);
	}

	Texture::~Texture()
	{
		if(_id != 0)
		{
			glDeleteTextures(1, &_id);
		}
	}

    void Texture::setImage(const Image& img, GLint lodLevel)
    {
        bind();
        glTexImage2D(_target, lodLevel, img.getInternalFormat(),
            img.getWidth(), img.getHeight(), img.getBorder(),
            img.getFormat(), img.getType(), img.getData().ptr());
    }

	GLuint Texture::getId() const
	{
		return _id;
	}

    void Texture::bind()
    {
        glBindTexture(_target, _id);
    }

    void Texture::activate(size_t pos)
    {
        bind();
        glActiveTexture(GL_TEXTURE0 + pos);
    }
}
