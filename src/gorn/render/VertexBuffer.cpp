
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/base/Data.hpp>

namespace gorn
{
    std::map<GLenum, GLuint> VertexBuffer::s_currentIds;

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
			GLenum target = getGlTarget(_target);
			if (s_currentIds[target] == _id)
			{
				s_currentIds[target] = 0;
			}
        }
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

        checkGlError("setting the data of a vertex buffer");
    }

    void VertexBuffer::setSubData(const Data& data, size_t offset)
    {
        bind();
		glBufferSubData(getGlTarget(_target), offset,
            data.size(), data.ptr());

        checkGlError("setting the a part of the data of a vertex buffer");
    }

    size_t VertexBuffer::getSize() const
    {
        return _size;
    }

}

