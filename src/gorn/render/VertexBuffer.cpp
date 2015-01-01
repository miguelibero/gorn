
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/base/Data.hpp>

namespace gorn
{
    VertexBuffer::VertexBuffer(const Data& data, Usage usage, Target target):
    _id(0), _target(target)
    {
        setData(data, usage);
    }

    VertexBuffer::VertexBuffer(Target target):
    _id(0), _target(target)
    {
    }
	
	VertexBuffer::~VertexBuffer()
    {
        if(_id != 0)
        {
            glDeleteBuffers(1, &_id);
        }
    }

    GLuint VertexBuffer::getId() const
    {
        if(_id == 0)
        {
            glGenBuffers(1, &_id);
        }
        return _id;
	};

    GLenum getGlTarget(VertexBufferTarget target)
    {
        switch(target)
        {
            default:
                return GL_ARRAY_BUFFER;
        }
    }

    GLenum getGlUsage(VertexBufferUsage usage)
    {
        switch(usage)
        {
            case VertexBufferUsage::StreamDraw:
                return GL_STREAM_DRAW;
			case VertexBufferUsage::StreamRead:
                return GL_STREAM_READ;
			case VertexBufferUsage::StreamCopy:
                return GL_STREAM_COPY;
			case VertexBufferUsage::StaticDraw:
                return GL_STATIC_DRAW;
			case VertexBufferUsage::StaticRead:
                return GL_STATIC_READ;
			case VertexBufferUsage::StaticCopy:
                return GL_STATIC_COPY;
			case VertexBufferUsage::DynamicRead:
                return GL_DYNAMIC_READ;
			case VertexBufferUsage::DynamicCopy:
                return GL_DYNAMIC_COPY;
            default:
                return GL_DYNAMIC_DRAW;
        }
    }

    void VertexBuffer::bind() const
    {
        GLenum target = getGlTarget(_target);
		glBindBuffer(target, getId());
    }

    void VertexBuffer::setData(const Data& data, Usage usage)
    {
        GLenum target = getGlTarget(_target);
		glBindBuffer(target, getId());
		glBufferData(target, data.size(), data.ptr(),
            getGlUsage(usage));
    }

    void VertexBuffer::setSubData(const Data& data, size_t offset)
    {
        GLenum target = getGlTarget(_target);
        glBindBuffer(target, getId());
		glBufferSubData(target, offset, data.size(), data.ptr());
    }

    Data VertexBuffer::getSubData(size_t offset, size_t size) const
    {
        GLenum target = getGlTarget(_target);
        Data data(size);
        glBindBuffer(target, getId());
		glGetBufferSubData(target, offset, data.size(), data.ptr());
        return data;
    }

}

