#include <gorn/render/Texture.hpp>
#include <gorn/render/Image.hpp>

namespace gorn
{
    std::map<GLenum, GLuint> Texture::s_currentIds;
    std::map<size_t, GLuint> Texture::s_activeIds;

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

        glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

	GLuint Texture::getId() const
	{
		return _id;
	}

    void Texture::bind()
    {
        if(s_currentIds[_target] != _id)
        {
            glBindTexture(_target, _id);
            s_currentIds[_target] = _id;
        }
    }

    void Texture::activate(size_t pos)
    {
        bind();
        if(s_activeIds[pos] != _id)
        {
            glActiveTexture(GL_TEXTURE0 + pos);
            s_activeIds[pos] = _id;
        }
    }
}
