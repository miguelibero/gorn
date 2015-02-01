#ifndef __gorn__AttributeDefinition__
#define __gorn__AttributeDefinition__

#include <gorn/render/Enums.hpp>
#include <string>

namespace gorn
{
    class VertexArray;
    class VertexBuffer;
    class Program;

	class AttributeDefinition
	{
    private:
        std::string _name;
        bool _normalized;
        BasicType _type;
        size_t _count;
        size_t _stride;
        size_t _offset;

	public:

        AttributeDefinition(const std::string& name="");

        AttributeDefinition& withName(const std::string& name);
        AttributeDefinition& withType(BasicType type);
        AttributeDefinition& withNormalized(bool enabled);
        AttributeDefinition& withCount(size_t count);
        AttributeDefinition& withStride(size_t stride);
        AttributeDefinition& withOffset(size_t offset);

        const std::string& getName() const;
        BasicType getType() const;
        bool getNormalized() const;
        size_t getCount() const;
        size_t getStride() const;
        size_t getOffset() const;
        size_t getTypeSize() const;
        size_t getMemSize() const;
	};
}

#endif

