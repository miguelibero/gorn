#include <gorn/render/AttributeBindingDefinition.hpp>

namespace gorn
{
    AttributeBindingDefinition::AttributeBindingDefinition():
    _normalized(false),
    _size(1),
    _stride(0),
    _offset(0)
    {
    }

    AttributeBindingDefinition& AttributeBindingDefinition::withName(const std::string& name)
    {
        _name = name;
        return *this;
    }

    AttributeBindingDefinition& AttributeBindingDefinition::withType(GLenum type)
    {
        _type = type;
        return *this;
    }

    AttributeBindingDefinition& AttributeBindingDefinition::withNormalized(GLboolean enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeBindingDefinition& AttributeBindingDefinition::withSize(GLint size)
    {
        _size = size;
        return *this;
    }

    AttributeBindingDefinition& AttributeBindingDefinition::withStride(GLsizei stride)
    {
        _stride = stride;
        return *this;
    }

    AttributeBindingDefinition& AttributeBindingDefinition::withOffset(GLsizei offset)
    {
        _offset = offset;
        return *this;
    }

    const std::string& AttributeBindingDefinition::getName() const
    {
        return _name;
    }

    GLenum AttributeBindingDefinition::getType() const
    {
        return _type;
    }

    bool AttributeBindingDefinition::getNormalized() const
    {
        return _normalized;
    }

    GLint AttributeBindingDefinition::getSize() const
    {
        return _size;
    }

    GLsizei AttributeBindingDefinition::getStride() const
    {
        return _stride;
    }

    GLsizei AttributeBindingDefinition::getOffset() const
    {
        return _offset;
    }
}
