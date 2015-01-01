#ifndef __gorn__AttributeBinding__
#define __gorn__AttributeBinding__

#include <gorn/render/Gl.hpp>
#include <string>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

	class AttributeBinding
	{
    private:
        VertexArray& _vao;
        const VertexBuffer& _vbo;
        const Program* _program;
        GLenum _type;
        GLint _attribute;
        bool _typeDefined;
        GLboolean _normalized;
        bool _normalizedDefined;
        GLint _size;
        GLsizei _stride;
        const GLvoid* _offset;

        void init();
	public:

        AttributeBinding(VertexArray& vao, const VertexBuffer& vbo);
        AttributeBinding(VertexArray& vao, const VertexBuffer& vbo,
            const Program& program);

        AttributeBinding& setAttribute(GLuint attr);
        AttributeBinding& setAttribute(const std::string& name);
        AttributeBinding& setType(GLenum type);
        AttributeBinding& setNormalized(GLboolean enabled);
        AttributeBinding& setSize(GLint size);
        AttributeBinding& setStride(GLsizei stride);
        AttributeBinding& setOffset(const GLvoid* offset);

        void create();
	};
}

#endif

