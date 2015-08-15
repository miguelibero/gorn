
#include <gorn/gl/VertexArray.hpp>
#include <gorn/gl/VertexBuffer.hpp>
#include <gorn/gl/Program.hpp>
#include <gorn/gl/Material.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/base/Exception.hpp>
#include <algorithm>

namespace gorn
{
    GLuint VertexArray::s_currentId = 0;

    VertexArray::VertexArray():
    _id(0), _elementType(BasicType::None)
    {   
    }
	
	VertexArray::~VertexArray()
    {
        cleanup();
    }

    void VertexArray::cleanup()
    {
        if(_id != 0)
        {
            if(s_currentId == _id)
            {
                s_currentId = 0;
            }
            glDeleteVertexArrays(1, &_id);
            checkGlError("deleting a vertex array");
        }
    }

    VertexArray::VertexArray(VertexArray&& other):
    _id(other._id),
    _elementVbo(std::move(other._elementVbo)),
    _elementType(other._elementType),
    _vertexVbos(std::move(other._vertexVbos)),
    _program(std::move(other._program)),
    _material(std::move(other._material))
    {
        other._elementType = BasicType::None;
        other._id = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other)
    {
        if(this != &other)
        {
            if(_id != other._id)
            {
                cleanup();
            }
            _id = other._id;
            _elementVbo = std::move(other._elementVbo);
            _elementType = other._elementType;
            _vertexVbos = std::move(other._vertexVbos);
            _program = std::move(other._program);
            _material = std::move(other._material);
            other._elementType = BasicType::None;
            other._id = 0;
        }
        return *this;
    }

    GLuint VertexArray::getId() const
    {
        if(_id == 0)
        {
            glGenVertexArrays(1, &_id);
			checkGlError("generating a vertex array");
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
        unbind();
        vbo->unbind();
    }

    void VertexArray::bindId(GLuint id)
    {
        if(s_currentId != id)
        {
		    glBindVertexArray(id);
            s_currentId = id;
        }
    }

    void VertexArray::bind() const
    {
	    bindId(getId());
    }

    void VertexArray::unbind()
    {
	    bindId(0);
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
 
        auto stride = def.getStride();
        if(def.getStrideType() != BasicType::None)
        {
            stride *= getBasicTypeSize(def.getStrideType());
        }
        auto offset = def.getOffset();
        if(def.getOffsetType() != BasicType::None)
        {
            offset *= getBasicTypeSize(def.getOffsetType());
        }
		glVertexAttribPointer(id, (GLint)def.getCount(),
            getGlBasicType(def.getType()),
            def.getNormalized(), (GLsizei)stride, (GLvoid*)offset);

        checkGlError("setting a vertex array attribute");
        glEnableVertexAttribArray(0);
        unbind();
        vbo->unbind();
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

    void VertexArray::setUniformValues(const UniformValueMap& values)
    {
        for(auto itr = values.begin(); itr != values.end(); ++itr)
        {
            setUniformValue(itr->first, itr->second);
        }
    }

    void VertexArray::draw(size_t count, size_t offset)
    {
        draw(count, DrawMode::Triangles, offset);
    }

    void VertexArray::draw(size_t count, DrawMode mode, size_t offset)
    {
        activate();
        GLenum glMode = getGlDrawMode(mode);
        if(_elementVbo && _elementType != BasicType::None)
        {
    		glDrawElements(glMode, (GLsizei)count, getGlBasicType(_elementType),
                reinterpret_cast<const GLvoid*>(offset));
        }
        else
        {
		    glDrawArrays(glMode, (GLint)offset, (GLsizei)count);
        }

        checkGlError("drawing a vertex array");
        unbind();
    }
}

