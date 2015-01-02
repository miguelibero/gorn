#ifndef __gorn__VertexArray__
#define __gorn__VertexArray__

#include <gorn/render/Gl.hpp>

namespace gorn
{
    class VertexBuffer;
    class VertexDefinition;
    class AttributeBinding;
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
        AttributeBinding bindAttribute(const VertexBuffer& vbo);
        AttributeBinding bindAttribute(const VertexBuffer& vbo, const Program& prog);
	    void bindElements(const VertexBuffer& elements);
	    void bindTransformFeedback(GLuint index, const VertexBuffer& buffer);
        void load(const VertexDefinition& vdef, const VertexBuffer& vbo, const Program& prog);
    };
}

#endif
