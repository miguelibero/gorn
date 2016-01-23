#ifndef __gorn__VertexDefinition__
#define __gorn__VertexDefinition__

#include <gorn/gl/AttributeDefinition.hpp>
#include <map>

namespace gorn
{
    class VertexDefinition
    {
    private:
        std::map<std::string, AttributeDefinition> _attributes;

    public:

        VertexDefinition();

        VertexDefinition& operator+=(const VertexDefinition& other);
        VertexDefinition operator+(const VertexDefinition& other) const;

        VertexDefinition& withAttribute(const AttributeDefinition& attr);
        AttributeDefinition& setAttribute(const std::string& name);

        const std::map<std::string, AttributeDefinition>& getAttributes() const;
        std::map<std::string, AttributeDefinition>& getAttributes();

        size_t getElementSize() const;
    };
}

#endif

