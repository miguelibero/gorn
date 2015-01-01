#ifndef __gorn__AttributeDefinition__
#define __gorn__AttributeDefinition__

#include <gorn/render/Gl.hpp>
#include <string>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

	class AttributeDefinition
	{
    private:
        VertexArray& _vao;
        const VertexBuffer& _vbo;
        const Program* _program;
        GLenum _type;
        GLint _attribute;
        bool _typeDefined;
        GLboolean _normalized;
        GLint _size;
        GLsizei _stride;
        GLsizei _offset;

        void init();
	public:

        AttributeDefinition(VertexArray& vao, const VertexBuffer& vbo);
        AttributeDefinition(VertexArray& vao, const VertexBuffer& vbo,
            const Program& program);

        AttributeDefinition& setAttribute(GLuint attr);
        AttributeDefinition& setAttribute(const std::string& name);
        AttributeDefinition& setType(GLenum type);
        AttributeDefinition& setNormalized(GLboolean enabled);
        AttributeDefinition& setSize(GLint size);
        AttributeDefinition& setStride(GLsizei stride);
        AttributeDefinition& setOffset(GLsizei offset);

        void bind();
	};
}

#endif

