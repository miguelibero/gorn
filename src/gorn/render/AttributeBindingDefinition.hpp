#ifndef __gorn__AttributeBindingDefinition__
#define __gorn__AttributeBindingDefinition__

#include <gorn/render/Gl.hpp>
#include <string>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

	class AttributeBindingDefinition
	{
    private:
        GLenum _type;
        std::string _name;
        GLboolean _normalized;
        GLint _size;
        GLsizei _stride;
        GLsizei _offset;

	public:

        AttributeBindingDefinition();


        AttributeBindingDefinition& withName(const std::string& name);
        AttributeBindingDefinition& withType(GLenum type);
        AttributeBindingDefinition& withNormalized(GLboolean enabled);
        AttributeBindingDefinition& withSize(GLint size);
        AttributeBindingDefinition& withStride(GLsizei stride);
        AttributeBindingDefinition& withOffset(GLsizei offset);

        const std::string& getName() const;
        GLenum getType() const;
        bool getNormalized() const;
        GLint getSize() const;
        GLsizei getStride() const;
        GLsizei getOffset() const;
	};
}

#endif

