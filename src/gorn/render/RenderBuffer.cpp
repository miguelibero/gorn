#include <gorn/render/RenderBuffer.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    GLuint RenderBuffer::s_currentId = 0;

	RenderBuffer::RenderBuffer(const glm::vec2& size, GLenum format):
	_id(0), _size(size), _format(format)
	{
	}

    void RenderBuffer::cleanup()
    {
        if(s_currentId == _id)
        {
            s_currentId = 0;
        }
        if(_id != 0 && glIsRenderbuffer(_id) == GL_TRUE)
        {
            glDeleteRenderbuffers(1, &_id);
            checkGlError("deleting render buffer");
        }
    }


    RenderBuffer::RenderBuffer(RenderBuffer&& other):
    _id(other._id), _size(other._size), _format(other._format)
    {
        other._id = 0;
    }

    RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other)
    {
        if(this != &other)
        {
            if(_id != other._id)
            {
                cleanup();
            }
            _id = other._id;
            _size = other._size;
            _format = other._format;
            other._id = 0;
        }
        return *this;
    }

	RenderBuffer::~RenderBuffer()
	{
       cleanup();
	}

	GLuint RenderBuffer::getId() const
	{
        if(_id == 0)
        {
            glGenRenderbuffers(1, &_id);
            if(_id == 0)
            {
                throw Exception("Could not create render buffer.");
            }
            auto oldId = s_currentId;
            bindId(_id);
            glRenderbufferStorage(GL_RENDERBUFFER, _format, _size.x, _size.y);
            bindId(oldId);
        }
		return _id;
	}

    void RenderBuffer::bind() const
    {
        bindId(_id);
    }

    void RenderBuffer::bindId(GLuint id)
    {
        if(s_currentId != id)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, id);
            checkGlError("binding render buffer");
            s_currentId = id;
        }
    }

    void RenderBuffer::unbind()
    {
        bindId(0);
    }

    void RenderBuffer::setParameter(GLenum param, int value)
    {
        auto oldId = s_currentId;
        bindId(_id);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, param, &value);
        checkGlError("setting render buffer parameter");
        bindId(oldId);
    }

    void RenderBuffer::attachToFrameBufferAsColor(int pos)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0+pos,
            GL_RENDERBUFFER, getId());
        checkGlError("attaching render buffer to frame buffer");
    }

    void RenderBuffer::attachToFrameBufferAsDepth()
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_RENDERBUFFER, getId());
        checkGlError("attaching render buffer to frame buffer");
    }

}
