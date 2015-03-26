#include <gorn/render/VertexDefinition.hpp>

namespace gorn
{
    VertexDefinition::VertexDefinition()
    {
    }

    VertexDefinition& VertexDefinition::operator+=(
        const VertexDefinition& other)
    {
        _attributes.insert(other._attributes.begin(), other._attributes.end());
        return *this;
    }

    VertexDefinition VertexDefinition::operator+(
        const VertexDefinition& other) const
    {
        VertexDefinition sum(*this);
        sum += other;
        return sum;
    }

    VertexDefinition& VertexDefinition::withAttribute(
        const AttributeDefinition& attr)
    {
        _attributes[attr.getName()] = attr;
        return *this;
    }

    AttributeDefinition& VertexDefinition::setAttribute(const std::string& name)
    {
        auto itr = _attributes.find(name);
        if(itr == _attributes.end())
        {
            itr = _attributes.insert(itr, {name, AttributeDefinition(name)});
        }
        return itr->second;
    }

    const std::map<std::string, AttributeDefinition>&
        VertexDefinition::getAttributes() const
    {
        return _attributes;
    }

    std::map<std::string, AttributeDefinition>&
        VertexDefinition::getAttributes()
    {
        return _attributes;
    }

    size_t VertexDefinition::getElementSize() const
    {
        size_t size = 0;
        for(auto itr = _attributes.begin(); itr != _attributes.end(); ++itr)
        {
            size +=  itr->second.getElementSize();
        }
        return size;
    }
}

