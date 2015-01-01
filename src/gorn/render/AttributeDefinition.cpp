#include <gorn/render/AttributeDefinition.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    AttributeDefinition::AttributeDefinition(VertexArray& vao,
        const VertexBuffer& vbo):
    _vao(vao), _vbo(vbo), _program(nullptr)
    {
        init();
    }

    AttributeDefinition::AttributeDefinition(VertexArray& vao,
        const VertexBuffer& vbo, const Program& prog):
    _vao(vao), _vbo(vbo), _program(&prog)
    {
        init();
    }

    void AttributeDefinition::init()
    {
        _attribute = -1;
        _typeDefined = false;
        _normalized = false;
        _size = 1;
        _stride = 0;
        _offset = 0;
    }

    AttributeDefinition& AttributeDefinition::setAttribute(GLuint attr)
    {
        _attribute = attr;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::setAttribute(const std::string& name)
    {
        if(_program == nullptr)
        {
            throw Exception("no program defined");
        }
        _attribute = _program->getAttribute(name);
        return *this;
    }

    AttributeDefinition& AttributeDefinition::setType(GLenum type)
    {
        _type = type;
        _typeDefined = true;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::setNormalized(GLboolean enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::setSize(GLint size)
    {
        _size = size;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::setStride(GLsizei stride)
    {
        _stride = stride;
        return *this;
    }

    AttributeDefinition& AttributeDefinition::setOffset(GLsizei offset)
    {
        _offset = offset;
        return *this;
    }

    void AttributeDefinition::bind()
    {
        if(_attribute == -1)
        {
            throw Exception("no attribute defined");
        }
        if(!_typeDefined)
        {
            throw Exception("no type defined");
        }
        _vao.bind();
        _vbo.bind();
        if(_program != nullptr)
        {
            _program->use();
        }
		glEnableVertexAttribArray(_attribute);
		glVertexAttribPointer(_attribute, _size, _type, _normalized,
            _stride, reinterpret_cast<const GLvoid*>(_offset));
	}
}
