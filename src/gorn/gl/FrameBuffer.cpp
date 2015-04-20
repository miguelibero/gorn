#include <gorn/gl/FrameBuffer.hpp>
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

    void FrameBuffer::attach(
        const std::shared_ptr<Texture>& texture, AttachType type)
    {
        _textures[type].push_back(texture);
    }

    void FrameBuffer::attach(
        const std::shared_ptr<RenderBuffer>& buffer)
    {
        auto type = buffer->getType();
        _renderBuffers[type].push_back(buffer);
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

    GLenum FrameBuffer::getAttachTypeEnum(AttachType type)
    {
        switch(type)
        {
        case AttachType::Depth:
            return GL_DEPTH_ATTACHMENT;
        case AttachType::Color:
            return GL_COLOR_ATTACHMENT0;
        case AttachType::Stencil:
            return GL_STENCIL_ATTACHMENT;
        }
        return 0;
    }

    void FrameBuffer::activate()
    {
        bind();
        std::vector<GLenum> buffers;
        for(auto itr = _textures.begin(); itr != _textures.end(); ++itr)
        {
            GLenum type = getAttachTypeEnum(itr->first);
            for(auto& texture : itr->second)
            {
                texture->attachToFrameBuffer(type);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                buffers.push_back(type);
                if(itr->first == AttachType::Color)
                {
                    type++;
                }
            }
        }
        for(auto itr = _renderBuffers.begin(); itr != _renderBuffers.end(); ++itr)
        {
            GLenum type = getAttachTypeEnum(itr->first);
            for(auto& render : itr->second)
            {
                render->attachToFrameBuffer(type);
                buffers.push_back(type);
                if(itr->first == AttachType::Color)
                {
                    type++;
                }
            }
        }
        //glDrawBuffers(buffers.size(), buffers.data());
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
