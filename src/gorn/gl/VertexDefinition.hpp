#ifndef __gorn__VertexDefinition__
#define __gorn__VertexDefinition__

#include <gorn/gl/VertexAttributeDefinition.hpp>
#include <unordered_map>

namespace gorn
{
    class VertexDefinition
    {
	public:
		typedef VertexAttributeDefinition Attribute;
		typedef std::vector<Attribute> Attributes;
    private:
		Attributes _attributes;

    public:

        VertexDefinition();

        VertexDefinition& operator+=(const VertexDefinition& other);
        VertexDefinition operator+(const VertexDefinition& other) const;

        VertexDefinition& withAttribute(const Attribute& attr);
        Attribute& setAttribute(const AttributeKind& kind);

        const Attributes& getAttributes() const;
		Attributes& getAttributes();

        size_t getElementSize() const;
    };
}

#endif

