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
        GLenum _type;
        std::string _name;
        bool _normalized;
        GLint _count;
        GLsizei _stride;
        GLsizei _offset;

	public:

        AttributeDefinition(const std::string& name="");

        AttributeDefinition& withName(const std::string& name);
        AttributeDefinition& withType(GLenum type);
        AttributeDefinition& withNormalized(bool enabled);
        AttributeDefinition& withCount(GLint count);
        AttributeDefinition& withStride(GLsizei stride);
        AttributeDefinition& withOffset(GLsizei offset);

        const std::string& getName() const;
        GLenum getType() const;
        bool getNormalized() const;
        GLint getCount() const;
        GLsizei getStride() const;
        GLsizei getOffset() const;
        GLsizei getTypeSize() const;
        GLsizei getMemSize() const;
	};
}

#endif

