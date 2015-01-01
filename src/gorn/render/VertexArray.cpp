
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>

namespace gorn
{
    VertexArray::VertexArray():
    _id(0)
    {
        glGenVertexArrays(1, &_id);
    }
	
	VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &_id);
    }

    GLuint VertexArray::getId() const
    {
        return _id;
	};

    void VertexArray::bind() const
    {
		glBindVertexArray(_id);
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

