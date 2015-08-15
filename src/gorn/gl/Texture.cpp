#include <gorn/gl/Texture.hpp>
#include <gorn/gl/Enums.hpp>
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
        cleanup();
	}

    void Texture::cleanup()
    {
        if(s_currentIds[_target] == _id)
        {
            s_currentIds.erase(_target);
        }
        for(auto itr = s_activeIds.begin(); itr != s_activeIds.end();)
        {
            if(itr->second == _id)
            {
                s_activeIds.erase(itr++);
            }
            else
            {
                ++itr;
            }
        }
		if(_id != 0 && glIsTexture(_id) == GL_TRUE)
		{
			glDeleteTextures(1, &_id);
            checkGlError("deleting texture");
		}
    }

    Texture::Texture(Texture&& other):
    _id(other._id), _target(other._target), _size(other._size)
    {
        other._id = 0;
    }

    Texture& Texture::operator=(Texture&& other)
    {
        if(this != &other)
        {
            if(_id != other._id)
            {
                cleanup();
            }
            _id = other._id;
            _size = other._size;
            _target = other._target;
            other._id = 0;
        }
        return *this;
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
            format, type, img.getData().data());
        
        checkGlError("setting texture image");
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

    void Texture::attachToFrameBuffer(GLenum type)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
            type, _target, _id, 0);
        checkGlError("attaching texture to frame buffer");
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
