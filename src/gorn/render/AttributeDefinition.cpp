#include <gorn/render/AttributeDefinition.hpp>

namespace gorn
{
    AttributeDefinition::AttributeDefinition(const std::string& name):
    _name(name),
    _normalized(false),
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

    AttributeDefinition& AttributeDefinition::withType(GLenum type)
    {
        _type = type;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withNormalized(bool enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::withCount(GLint count)
    {
        _count = count;
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

    GLint AttributeDefinition::getCount() const
    {
        return _count;
    }

    GLsizei AttributeDefinition::getStride() const
    {
        return _stride;
    }

    GLsizei AttributeDefinition::getOffset() const
    {
        return _offset;
    }

    GLsizei AttributeDefinition::getTypeSize() const
    {
        switch(_type)
        {
            case GL_BYTE:
                return sizeof(GLbyte);
            case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
            case GL_SHORT:
                return sizeof(GLshort);
            case GL_UNSIGNED_SHORT:
                return sizeof(GLushort);
            case GL_INT:
                return sizeof(GLint);
            case GL_UNSIGNED_INT:
                return sizeof(GLuint);
            case GL_FLOAT:
                return sizeof(GLfloat);
            default:
                return 0;               
        }
    }

    GLsizei AttributeDefinition::getMemSize() const
    {
        return getTypeSize()*getCount();
    }

}
