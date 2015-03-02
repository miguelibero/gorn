#include <gorn/render/Texture.hpp>
#include <gorn/render/GlEnums.hpp>
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

    GLint getGlInternalFormat(ImageFormat f)
    {
        switch(f)
        {
        default:
            return 0;
        }
    }

    void Texture::setImage(const Image& img, GLint lodLevel)
    {
        bind();
        
        GLenum format = img.hasAlpha()?GL_RGBA:GL_RGB;
        GLenum type = getGlBasicType(img.getType());
        _size = img.getSize();
        GLint internalFormat = getGlInternalFormat(img.getFormat());
        if(internalFormat == 0)
        {
            internalFormat = format;
        }

        glTexImage2D(_target, lodLevel, internalFormat,
            (GLsizei)_size.x, (GLsizei)_size.y, 0,
            format, type, img.getData().ptr());
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
