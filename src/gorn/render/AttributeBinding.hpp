#ifndef __gorn__AttributeBinding__
#define __gorn__AttributeBinding__

#include <gorn/render/Gl.hpp>
#include <string>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;
    class AttributeBindingDefinition;

	class AttributeBinding
	{
    public:
        typedef AttributeBindingDefinition Definition;
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

        AttributeBinding(VertexArray& vao, const VertexBuffer& vbo);
        AttributeBinding(VertexArray& vao, const VertexBuffer& vbo,
            const Program& program);

        AttributeBinding& withDefinition(const Definition& def);    
        AttributeBinding& withAttribute(GLuint attr);
        AttributeBinding& withAttribute(const std::string& name);
        AttributeBinding& withType(GLenum type);
        AttributeBinding& withNormalized(GLboolean enabled);
        AttributeBinding& withSize(GLint size);
        AttributeBinding& withStride(GLsizei stride);
        AttributeBinding& withOffset(GLsizei offset);

        void finish();
	};
}

#endif

