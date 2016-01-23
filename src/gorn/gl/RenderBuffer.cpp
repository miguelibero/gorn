#include <gorn/gl/RenderBuffer.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    GLuint RenderBuffer::s_currentId = 0;

    RenderBuffer::RenderBuffer(const glm::vec2& size, Type type):
    _id(0), _size(size), _type(type)
    {
    }

    RenderBuffer::Type RenderBuffer::getType() const
    {
        return _type;
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

    GLenum RenderBuffer::getTypeFormat(Type type)
    {
        switch(type)
        {
        case Type::Depth:
            return GL_DEPTH_COMPONENT16;
        case Type::Color:
            return GL_RGBA;
        case Type::Stencil:
            return GL_STENCIL_INDEX8;
        }
        return 0;
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
            glRenderbufferStorage(GL_RENDERBUFFER,
                getTypeFormat(_type), (GLsizei)_size.x, (GLsizei)_size.y);

            int w = (int)_size.x;
            int h = (int)_size.y;
            glGetRenderbufferParameteriv(GL_RENDERBUFFER,
                GL_RENDERBUFFER_WIDTH, &w);
            glGetRenderbufferParameteriv(GL_RENDERBUFFER,
                GL_RENDERBUFFER_HEIGHT, &h);

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

    void RenderBuffer::attachToFrameBuffer(GLenum type)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
            type, GL_RENDERBUFFER, getId());
        checkGlError("attaching render buffer to frame buffer");
    }

}
