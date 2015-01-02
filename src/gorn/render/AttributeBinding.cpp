#include <gorn/render/AttributeBinding.hpp>
#include <gorn/render/AttributeBindingDefinition.hpp>
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
        init();
    }

    AttributeBinding::AttributeBinding(VertexArray& vao,
        const VertexBuffer& vbo, const Program& prog):
    _vao(vao), _vbo(vbo), _program(&prog)
    {
        init();
    }

    void AttributeBinding::init()
    {
        _attribute = -1;
        _typeDefined = false;
        _normalized = false;
        _size = 1;
        _stride = 0;
        _offset = 0;
    }

    AttributeBinding& AttributeBinding::withDefinition(const Definition& def)
    {
        withAttribute(def.getName());
        withType(def.getType());
        withNormalized(def.getNormalized());
        withSize(def.getSize());
        withStride(def.getStride());
        withOffset(def.getOffset());
        return *this;
    }

    AttributeBinding& AttributeBinding::withAttribute(GLuint attr)
    {
        _attribute = attr;
        return *this;
    }

    AttributeBinding& AttributeBinding::withAttribute(const std::string& name)
    {
        if(_program == nullptr)
        {
            throw Exception("no program defined");
        }
        _attribute = _program->getAttribute(name);
        return *this;
    }

    AttributeBinding& AttributeBinding::withType(GLenum type)
    {
        _type = type;
        _typeDefined = true;
        return *this;
    }

    AttributeBinding& AttributeBinding::withNormalized(GLboolean enabled)
    {
        _normalized = enabled;
        return *this;
    }

    AttributeBinding& AttributeBinding::withSize(GLint size)
    {
        _size = size;
        return *this;
    }

    AttributeBinding& AttributeBinding::withStride(GLsizei stride)
    {
        _stride = stride;
        return *this;
    }

    AttributeBinding& AttributeBinding::withOffset(GLsizei offset)
    {
        _offset = offset;
        return *this;
    }

    void AttributeBinding::finish()
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
