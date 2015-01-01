
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/AttributeDefinition.hpp>

namespace gorn
{
    VertexArray::VertexArray():
    _id(0)
    {   
    }
	
	VertexArray::~VertexArray()
    {
        if(_id != 0)
        {
            glDeleteVertexArrays(1, &_id);
        }
    }

    GLuint VertexArray::getId() const
    {
        if(_id == 0)
        {
            glGenVertexArrays(1, &_id);
        }
        return _id;
	};

    void VertexArray::bind() const
    {
		glBindVertexArray(getId());
    }

    AttributeDefinition VertexArray::defineAttribute(const VertexBuffer& vbo)
    {
        return AttributeDefinition(*this, vbo);
    }

    AttributeDefinition VertexArray::defineAttribute(const VertexBuffer& vbo, const Program& prog)
    {
        return AttributeDefinition(*this, vbo, prog);
    }

	void VertexArray::bindElements(const VertexBuffer& elements)
	{
        bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements.getId());
	}

	void VertexArray::bindTransformFeedback(GLuint index, const VertexBuffer& buffer)
	{
        bind();
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer.getId());
	}
}

