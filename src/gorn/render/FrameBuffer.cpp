#include <gorn/render/FrameBuffer.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    GLuint FrameBuffer::s_currentId = 0;

	FrameBuffer::FrameBuffer():
	_id(0)
	{
	}

    void FrameBuffer::cleanup()
    {
        if(s_currentId == _id)
        {
            s_currentId = 0;
        }
        if(_id != 0 && glIsFramebuffer(_id) == GL_TRUE)
        {
            glDeleteFramebuffers(1, &_id);
            checkGlError("deleting frame buffer");
        }
    }


    FrameBuffer::FrameBuffer(FrameBuffer&& other):
    _id(other._id)
    {
        other._id = 0;
    }

    FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other)
    {
        if(this != &other)
        {
            if(_id != other._id)
            {
                cleanup();
            }
            _id = other._id;
            other._id = 0;
        }
        return *this;
    }

	FrameBuffer::~FrameBuffer()
	{
       cleanup();
	}

    void FrameBuffer::setTexture(const std::shared_ptr<Texture>& texture)
    {
        _texture = texture;
    }

    void FrameBuffer::setRenderBuffer(
        const std::shared_ptr<RenderBuffer>& buffer)
    {
        _render = buffer;
    }

	GLuint FrameBuffer::getId() const
	{
        if(_id == 0)
        {
            glGenFramebuffers(1, &_id);
        }
        if(_id == 0)
        {
            throw Exception("Could not create frame buffer.");
        }
		return _id;
	}

    void FrameBuffer::bindId(GLuint id)
    {
        if(s_currentId != id)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, id);
            checkGlError("binding frame buffer");
            s_currentId = id;
        }
    }

    void FrameBuffer::bind() const
    {
        bindId(getId());
    }

    void FrameBuffer::activate()
    {
        bind();
        std::vector<GLenum> buffers;
        if(_render != nullptr)
        {
            _render->attachToFrameBufferAsDepth();
            buffers.push_back(GL_DEPTH_ATTACHMENT);
        }
        if(_texture != nullptr)
        {
            _texture->attachToFrameBufferAsColor(0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            buffers.push_back(GL_COLOR_ATTACHMENT0);
        }
        glDrawBuffers(buffers.size(), buffers.data());
        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if(status != GL_FRAMEBUFFER_COMPLETE)
        {
            throw Exception("Could not setup frame buffer.");
        }
        checkGlError("setting up frame buffer");
    }

    void FrameBuffer::unbind()
    {
        bindId(0);
    }

}
