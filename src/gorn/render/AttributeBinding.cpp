#include <gorn/render/AttributeBinding.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    AttributeBinding::AttributeBinding(VertexArray& vao,
        const VertexBuffer& vbo):
    _vao(vao), _vbo(vbo), _program(nullptr)
    {
    }

    AttributeBinding::AttributeBinding(VertexArray& vao,
        const VertexBuffer& vbo, const Program& prog):
    _vao(vao), _vbo(vbo), _program(&prog)
    {
    }

    void AttributeBinding::init()
    {
        _attribute = -1;
        _typeDefined = false;
        _normalizedDefined = false;
        _size = 1;
        _stride = 0;
        _offset = 0;
    }

    AttributeBinding& AttributeBinding::setAttribute(GLuint attr)
    {
        _attribute = attr;
        return *this;
    }

    AttributeBinding& AttributeBinding::setAttribute(const std::string& name)
    {
        if(_program == nullptr)
        {
            throw Exception("no program defined");
        }
        _attribute = _program->getAttribute(name);
        return *this;
    }

    AttributeBinding& AttributeBinding::setType(GLenum type)
    {
        _type = type;
        _typeDefined = true;
        if(!_normalizedDefined)
        {
            _normalized = type == GL_FLOAT
                || type == GL_HALF_FLOAT
                || type == GL_DOUBLE;
        }
        return *this;
    }

    AttributeBinding& AttributeBinding::setNormalized(GLboolean enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeBinding& AttributeBinding::setSize(GLint size)
    {
        _size = size;
        return *this;
    }

    AttributeBinding& AttributeBinding::setStride(GLsizei stride)
    {
        _stride = stride;
        return *this;
    }

    AttributeBinding& AttributeBinding::setOffset(const GLvoid* offset)
    {
        _offset = offset;
        return *this;
    }

    void AttributeBinding::create()
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
		glEnableVertexAttribArray(_attribute);
		glVertexAttribPointer(_attribute, _size, _type, _normalized,
            _stride, _offset);
	}
}
