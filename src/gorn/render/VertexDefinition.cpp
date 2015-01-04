#include <gorn/render/VertexDefinition.hpp>

namespace gorn
{
    VertexDefinition::VertexDefinition()
    {
    }

    VertexDefinition& VertexDefinition::withAttribute(const AttributeDefinition& attr)
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

    const std::map<std::string, AttributeDefinition>& VertexDefinition::getAttributes() const
    {
        return _attributes;
    }    
}

