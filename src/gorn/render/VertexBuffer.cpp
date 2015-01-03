
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/base/Data.hpp>

namespace gorn
{
    std::map<GLenum, GLuint> VertexBuffer::s_currentIds;

    VertexBuffer::VertexBuffer(const Data& data, Usage usage, Target target):
    _id(0), _target(target), _size(0)
    {
        setData(data, usage);
    }

    VertexBuffer::VertexBuffer(Target target):
    _id(0), _target(target), _size(0)
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
            case VertexBufferTarget::ElementArrayBuffer:
                return GL_ELEMENT_ARRAY_BUFFER;
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
        GLuint id = getId();
        if(s_currentIds[target] != id)
        {
		    glBindBuffer(target, id);
            s_currentIds[target] = id;
        }
    }

    void VertexBuffer::setData(const Data& data, Usage usage)
    {
        bind();
        _size = data.size();
		glBufferData(getGlTarget(_target), data.size(),
            data.ptr(), getGlUsage(usage));
    }

    void VertexBuffer::setSubData(const Data& data, size_t offset)
    {
        bind();
		glBufferSubData(getGlTarget(_target), offset,
            data.size(), data.ptr());
    }

    Data VertexBuffer::getSubData(size_t offset, size_t size) const
    {
        bind();
        Data data(size);
		glGetBufferSubData(getGlTarget(_target),
            offset, data.size(), data.ptr());
        return data;
    }

    size_t VertexBuffer::getSize() const
    {
        return _size;
    }

}

