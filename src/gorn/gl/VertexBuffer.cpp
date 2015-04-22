
#include <gorn/gl/VertexBuffer.hpp>
#include <buffer.hpp>

namespace gorn
{
	GLenum getGlTarget(VertexBufferTarget target)
	{
		switch (target)
		{
		case VertexBufferTarget::ElementArrayBuffer:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			return GL_ARRAY_BUFFER;
		}
	}

	GLenum getGlUsage(VertexBufferUsage usage)
	{
		switch (usage)
		{
		case VertexBufferUsage::StreamDraw:
			return GL_STREAM_DRAW;
		case VertexBufferUsage::StaticDraw:
			return GL_STATIC_DRAW;
		default:
			return GL_DYNAMIC_DRAW;
		}
	}


    VertexBuffer::VertexBuffer(const buffer& data, Usage usage, Target target):
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
        cleanup();
    }

    void VertexBuffer::cleanup()
    {
        if(_id != 0)
        {
            glDeleteBuffers(1, &_id);
            checkGlError("deleting a vertex buffer");
        }
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other):
    _id(other._id),
    _target(other._target),
    _size(other._size)
    {
        other._size = 0;
        other._id = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
    {
        if(this != &other)
        {
            if(_id != other._id)
            {
                cleanup();
            }
		    _id = other._id;
            _target = other._target;
            _size = other._size;
            other._size = 0;
            other._id = 0;
        }
        return *this;
    }

    GLuint VertexBuffer::getId() const
    {
        if(_id == 0)
        {
            glGenBuffers(1, &_id);
			checkGlError("generating a vertex buffer");
        }
        return _id;
	};

    void VertexBuffer::bindId(GLuint id, GLenum target)
    {
        glBindBuffer(target, id);
    }

    void VertexBuffer::bind() const
    {
        bindId(getId(), getGlTarget(_target));
    }

    void VertexBuffer::unbind() const
    {
        bindId(0, getGlTarget(_target));
    }

    void VertexBuffer::setData(const buffer& data, Usage usage)
    {
        bind();
        _size = data.size();
		glBufferData(getGlTarget(_target), data.size(),
            data.data(), getGlUsage(usage));

        checkGlError("setting the data of a vertex buffer");
    }

    void VertexBuffer::setSubData(const buffer& data, size_t offset)
    {
        bind();
		glBufferSubData(getGlTarget(_target), offset,
            data.size(), data.data());

        checkGlError("setting the a part of the data of a vertex buffer");
    }

    size_t VertexBuffer::getSize() const
    {
        return _size;
    }

}

