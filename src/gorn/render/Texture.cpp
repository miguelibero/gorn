#include <gorn/render/Texture.hpp>
#include <gorn/asset/Image.hpp>

namespace gorn
{
    std::map<GLenum, GLuint> Texture::s_currentIds;
    std::map<size_t, GLuint> Texture::s_activeIds;

	Texture::Texture(GLenum target):
	_id(0), _target(target)
	{
		glGenTextures(1, &_id);
	}

	Texture::~Texture()
	{
		if(_id != 0)
		{
			glDeleteTextures(1, &_id);
		}
	}

    void Texture::setParameter(GLenum name, GLint value)
    {
        bind();
        glTexParameteri(_target, name, value);
    }

    void Texture::setParameter(GLenum name, GLfloat value)
    {
        bind();
        glTexParameterf(_target, name, value);
    }

    void Texture::setParameter(GLenum name, const std::vector<GLint>& value)
    {
        bind();
        glTexParameteriv(_target, name, value.data());
    }

    void Texture::setParameter(GLenum name, const std::vector<GLfloat>& value)
    {
        bind();
        glTexParameterfv(_target, name, value.data());
    }

    void Texture::setImage(const Image& img, GLint lodLevel)
    {
        bind();
        glTexImage2D(_target, lodLevel, img.getInternalFormat(),
            img.getWidth(), img.getHeight(), img.getBorder(),
            img.getFormat(), img.getType(), img.getData().ptr());
        _size = glm::vec2(img.getWidth(), img.getHeight());
    }

	GLuint Texture::getId() const
	{
		return _id;
	}

    const glm::vec2& Texture::getSize() const
    {
        return _size;
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
            glActiveTexture(GL_TEXTURE0 + (GLenum)pos);
            s_activeIds[pos] = _id;
        }
    }
}
