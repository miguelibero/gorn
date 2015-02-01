
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/AttributeDefinition.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/render/Material.hpp>
#include <gorn/base/Exception.hpp>
#include <algorithm>

namespace gorn
{
    GLenum getGlDrawMode(DrawMode mode)
    {
        switch(mode)
        {
            case DrawMode::Quads:
                return GL_QUADS;
            case DrawMode::Lines:
                return GL_LINES;
            case DrawMode::Points:
                return GL_POINTS;
            case DrawMode::Triangles:
                return GL_TRIANGLES;
            default:
                throw Exception("Unsupported draw mode.");
        }
    }

    GLenum getGlBasicType(BasicType type)
    {
        switch(type)
        {
            case BasicType::Byte:
                return GL_BYTE;
            case BasicType::UnsignedByte:
                return GL_UNSIGNED_BYTE;
            case BasicType::Short:
                return GL_SHORT;
            case BasicType::UnsignedShort:
                return GL_UNSIGNED_SHORT;
            case BasicType::Integer:
                return GL_INT;
            case BasicType::UnsignedInteger:
                return GL_UNSIGNED_INT;
            case BasicType::Float:
                return GL_FLOAT;
            default:
                return 0;               
        }
    }

    GLuint VertexArray::s_currentId = 0;

    VertexArray::VertexArray():
    _id(0), _elementType(BasicType::None)
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

    void VertexArray::setProgram(const std::shared_ptr<Program>& program)
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

    void VertexArray::setMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
    }

    const std::shared_ptr<Material>& VertexArray::getMaterial() const
    {
        return _material;
    }

    void VertexArray::setElementData(const std::shared_ptr<VertexBuffer>& vbo, BasicType type)
    {
        _elementVbo = vbo;
        _elementType = type;
        bind();
        vbo->bind();
    }

    void VertexArray::bind() const
    {
        if(s_currentId != getId())
        {
		    glBindVertexArray(getId());
            s_currentId = getId();
        }
    }

    void VertexArray::activate() const
    {
        bind();
        if(_material != nullptr)
        {
            _material->activate();
        }
    }

    void VertexArray::setAttribute(const std::shared_ptr<VertexBuffer>& vbo,
        const AttributeDefinition& def)
    {
        if(def.getType() == BasicType::None)
        {
            throw Exception("no type defined");
        }

        auto itr = std::find(_vertexVbos.begin(), _vertexVbos.end(), vbo);
        if(itr == _vertexVbos.end())
        {
            itr = _vertexVbos.insert(itr, vbo);
        }
        auto program = getProgram();
        GLint id = program->getAttribute(def.getName());        

        bind();
        vbo->bind();
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, def.getCount(), 
            getGlBasicType(def.getType()),
            def.getNormalized(), def.getStride(),
            reinterpret_cast<const GLvoid*>(def.getOffset()));

        checkGlError("setting a vertex array attribute");
    }

    void VertexArray::addVertexData(const std::shared_ptr<VertexBuffer>& vbo,
        const VertexDefinition& def)
    {
        for(auto itr = def.getAttributes().begin();
            itr != def.getAttributes().end(); ++itr)
        {
            setAttribute(vbo, itr->second);
        }
    }

    void VertexArray::setUniformValue(const std::string& name, const UniformValue& value)
    {
        auto program = getProgram();
        if(program != nullptr)
        {
            program->setUniformValue(name, value);
        }
    }

    void VertexArray::setUniformValue(const GLint& location, const UniformValue& value)
    {
        auto program = getProgram();
        if(program != nullptr)
        {
            program->setUniformValue(location, value);
        }
    }

    void VertexArray::draw(size_t count, DrawMode mode, size_t offset)
    {
        activate();
        GLenum glMode = getGlDrawMode(mode);
        if(_elementVbo && _elementType != BasicType::None)
        {
    		glDrawElements(glMode, count, getGlBasicType(_elementType),
                reinterpret_cast<const GLvoid*>(offset));
        }
        else
        {
		    glDrawArrays(glMode, offset, count);
        }

        checkGlError("drawing a vertex array");
    }
}

