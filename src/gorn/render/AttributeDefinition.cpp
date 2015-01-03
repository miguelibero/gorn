#include <gorn/render/AttributeDefinition.hpp>

namespace gorn
{
    AttributeDefinition::AttributeDefinition(const std::string& name):
    _name(name),
    _normalized(false),
    _size(1),
    _stride(0),
    _offset(0)
    {
    }

    AttributeDefinition& AttributeDefinition::withName(const std::string& name)
    {
        _name = name;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withType(GLenum type)
    {
        _type = type;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withNormalized(GLboolean enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withSize(GLint size)
    {
        _size = size;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withStride(GLsizei stride)
    {
        _stride = stride;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withOffset(GLsizei offset)
    {
        _offset = offset;
        return *this;
    }

    const std::string& AttributeDefinition::getName() const
    {
        return _name;
    }

    GLenum AttributeDefinition::getType() const
    {
        return _type;
    }

    bool AttributeDefinition::getNormalized() const
    {
        return _normalized;
    }

    GLint AttributeDefinition::getSize() const
    {
        return _size;
    }

    GLsizei AttributeDefinition::getStride() const
    {
        return _stride;
    }

    GLsizei AttributeDefinition::getOffset() const
    {
        return _offset;
    }
}
