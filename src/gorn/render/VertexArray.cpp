
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/AttributeBinding.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/render/Material.hpp>
#include <algorithm>

namespace gorn
{
    GLuint VertexArray::_currentId;

    VertexArray::VertexArray():
    _id(0)
    {   
    }
	
	VertexArray::~VertexArray()
    {
        if(_id != 0)
        {
            glDeleteVertexArrays(1, &_id);
        }
    }

    GLuint VertexArray::getId() const
    {
        if(_id == 0)
        {
            glGenVertexArrays(1, &_id);
        }
        return _id;
	};

    void VertexArray::bindProgram(const std::shared_ptr<Program>& program)
    {
        _program = program;
        if(_program != nullptr)
        {
            bind();
            _program->use();
        }
    }

    const std::shared_ptr<Program>& VertexArray::getProgram() const
    {
        if(_material != nullptr)
        {
            return _material->getProgram();
        }
        return _program;
    }

    void VertexArray::bindMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
        if(_material != nullptr)
        {
            bind();
            _material->activate();
        }
    }

    const std::shared_ptr<Material>& VertexArray::getMaterial() const
    {
        return _material;
    }

    void VertexArray::bindData(const std::shared_ptr<VertexBuffer>& vbo)
    {
        addData(vbo);
        bind();
        vbo->bind();
    }

    void VertexArray::addData(const std::shared_ptr<VertexBuffer>& vbo)
    {
        auto itr = std::find(_vbos.begin(), _vbos.end(), vbo);
        if(itr == _vbos.end())
        {
            _vbos.insert(itr, vbo);
        }
    }

    void VertexArray::bind() const
    {
        if(_currentId != getId())
        {
		    glBindVertexArray(getId());
        }
    }

    AttributeBinding VertexArray::bindAttribute(const std::shared_ptr<VertexBuffer>& vbo)
    {
        addData(vbo);
        auto program = getProgram();
        if(program != nullptr)
        {
            return AttributeBinding(*this, *vbo, *program);
        }
        else
        {
            return AttributeBinding(*this, *vbo);
        }
    }

    void VertexArray::bindData(const VertexDefinition& vdef, const std::shared_ptr<VertexBuffer>& vbo)
    {
        for(auto itr = vdef.getAttributeBindings().begin();
            itr != vdef.getAttributeBindings().end(); ++itr)
        {
            bindAttribute(vbo).withDefinition(itr->second).finish();
        }
    }
}

