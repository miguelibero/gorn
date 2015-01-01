#ifndef __gorn__VertexArray__
#define __gorn__VertexArray__

#include <gorn/render/Gl.hpp>

namespace gorn
{
    class VertexBuffer;
    class AttributeDefinition;
    class Program;

	class VertexArray
	{
	private:
		mutable GLuint _id;

	public:
		VertexArray();
		~VertexArray();
		GLuint getId() const;

        void bind() const;
        void bindAttribute(GLuint attribute, VertexBuffer& buffer,
            GLenum type, GLboolean normalized, GLint size,
            GLsizei stride=0, GLsizei offset=0);
        AttributeDefinition defineAttribute(const VertexBuffer& vbo);
        AttributeDefinition defineAttribute(const VertexBuffer& vbo, const Program& prog);
	    void bindElements(const VertexBuffer& elements);
	    void bindTransformFeedback(GLuint index, const VertexBuffer& buffer);
    };
}

#endif
