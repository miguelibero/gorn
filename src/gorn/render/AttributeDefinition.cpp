#include <gorn/render/AttributeDefinition.hpp>

namespace gorn
{
    AttributeDefinition::AttributeDefinition(const std::string& name):
    _name(name),
    _normalized(false),
    _type(BasicType::None),
    _count(1),
    _stride(0),
    _offset(0)
    {
    }

    AttributeDefinition& AttributeDefinition::withName(const std::string& name)
    {
        _name = name;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withType(BasicType type)
    {
        _type = type;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withNormalized(bool enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withCount(size_t count)
    {
        _count = count;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withStride(size_t stride)
    {
        _stride = stride;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withOffset(size_t offset)
    {
        _offset = offset;
        return *this;
    }

    const std::string& AttributeDefinition::getName() const
    {
        return _name;
    }

    BasicType AttributeDefinition::getType() const
    {
        return _type;
    }

    bool AttributeDefinition::getNormalized() const
    {
        return _normalized;
    }

    size_t AttributeDefinition::getCount() const
    {
        return _count;
    }

    size_t AttributeDefinition::getStride() const
    {
        return _stride;
    }

    size_t AttributeDefinition::getOffset() const
    {
        return _offset;
    }

    size_t AttributeDefinition::getTypeSize() const
    {
        return getSize(_type);
    }

    size_t AttributeDefinition::getMemSize() const
    {
        return getTypeSize()*getCount();
    }

}
