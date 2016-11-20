#include <gorn/gl/VertexDefinition.hpp>
#include <algorithm>

namespace gorn
{
    VertexDefinition::VertexDefinition()
    {
    }

    VertexDefinition& VertexDefinition::operator+=(
        const VertexDefinition& other)
    {
		_attributes.insert(_attributes.end(), other._attributes.begin(), other._attributes.end());
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
        const Attribute& attr)
    {
        _attributes.push_back(attr);
        return *this;
    }

	VertexDefinition::Attribute& VertexDefinition::setAttribute(const AttributeKind& kind)
    {
		auto itr = std::find_if(_attributes.begin(), _attributes.end(), [&kind](const Attribute& attr){
			return attr.getKind() == kind;
		});
        if(itr == _attributes.end())
        {
            itr = _attributes.insert(itr, kind);
        }
        return *itr;
    }

    const VertexDefinition::Attributes& VertexDefinition::getAttributes() const
    {
        return _attributes;
    }

	VertexDefinition::Attributes& VertexDefinition::getAttributes()
    {
        return _attributes;
    }

    size_t VertexDefinition::getElementSize() const
    {
        size_t size = 0;
        for(auto itr = _attributes.begin(); itr != _attributes.end(); ++itr)
        {
            size +=  itr->getElementSize();
        }
        return size;
    }
}

