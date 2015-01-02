#include <gorn/render/VertexDefinition.hpp>

namespace gorn
{
    VertexDefinition::VertexDefinition()
    {
    }

    AttributeBindingDefinition& VertexDefinition::defineAttribute(const std::string& name)
    {
        auto itr = _attributeBindings.find(name);
        if(itr == _attributeBindings.end())
        {
            itr = _attributeBindings.insert(itr, {name, AttributeBindingDefinition()});
            itr->second.withName(name);
        }
        return itr->second;
    }

    const std::map<std::string, AttributeBindingDefinition>& VertexDefinition::getAttributeBindings() const
    {
        return _attributeBindings;
    }    
}

