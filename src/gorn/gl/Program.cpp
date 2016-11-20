#include <gorn/gl/Program.hpp>
#include <gorn/gl/ProgramDefinition.hpp>
#include <gorn/gl/UniformValue.hpp>
#include <gorn/base/Exception.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gorn
{
    GLuint Program::s_currentId = 0;

    Program::Program(const std::shared_ptr<Shader>& vertexShader,
        const std::shared_ptr<Shader>& fragmentShader):
    _id(0), _vertexShader(vertexShader), _fragmentShader(fragmentShader)
    {
        _id = glCreateProgram();
        if(_id == 0)
        {
            throw Exception("Could not create program.");
        }
        glAttachShader(_id, _fragmentShader->getId());
        checkGlError("attaching fragment shader");
        glAttachShader(_id, _vertexShader->getId());
        checkGlError("attaching vertex shader");
        glLinkProgram(_id);
        checkGlError("linking a program");
    }

    void Program::cleanup()
    {
        if(s_currentId == _id)
        {
            s_currentId = 0;
        }
        if(_id != 0 && glIsProgram(_id) == GL_TRUE)
        {
            glDeleteProgram(_id);
            checkGlError("deleting program");
        }
    }


    Program::Program(Program&& other):
    _id(other._id), _vertexShader(other._vertexShader),
    _fragmentShader(other._fragmentShader)
    {
        other._id = 0;
    }

    Program& Program::operator=(Program&& other)
    {
        if(this != &other)
        {
            if(_id != other._id)
            {
                cleanup();
            }
            _id = other._id;
            _vertexShader = std::move(other._vertexShader);
            _fragmentShader = std::move(other._fragmentShader);
            other._id = 0;
        }
        return *this;
    }

    Program::~Program()
    {
       cleanup();
    }

    GLuint Program::getId() const
    {
        return _id;
    }

    const Shader& Program::getFragmentShader() const
    {
        return *_fragmentShader;
    }

    const Shader& Program::getVertexShader() const
    {
        return *_vertexShader;
    }

    void Program::use() const
    {
        if(s_currentId != _id)
        {
            glUseProgram(_id);
            s_currentId = _id;
        }
    }

    void Program::loadDefinition(const Definition& def)
    {
        for(auto& adef : def.getAttributes())
        {
            getAttribute(adef.getKind());
        }
        for(auto& udef : def.getUniforms())
        {
            auto id = getUniform(udef.getKind());
            _uniforms[udef.getKind()] = id;
            if(!udef.getDefaultValue().empty())
            {
                setUniformValue(id, udef.getDefaultValue());
            }
        }
		_vertexDefinition = def.getVertexDefinition();
    }

	GLint Program::getAttribute(const AttributeKind& kind) const
    {
		for (auto itr = _attributes.begin();
			itr != _attributes.end(); ++itr)
		{
			if (itr->first.match(kind))
			{
				return itr->second;
			}
		}
		auto id = glGetAttribLocation(getId(), kind.getName().c_str());
		_attributes[kind] = id;
		return id;
    }

    GLint Program::getUniform(const UniformKind& kind) const
    {
		for (auto itr = _uniforms.begin();
			itr != _uniforms.end(); ++itr)
		{
			if (itr->first.match(kind))
			{
				return itr->second;
			}
		}
		auto id = glGetUniformLocation(getId(), kind.getName().c_str());
		_uniforms[kind] = id;
		return id;
    }

	const Program::AttributeMap& Program::getAttributes() const
	{
		return _attributes;
	}

	const Program::UniformMap& Program::getUniforms() const
	{
		return _uniforms;
	}

    bool Program::hasAttribute(const AttributeKind& kind) const
    {
        return getAttribute(kind) >= 0;
    }

    bool Program::hasUniform(const UniformKind& name) const
    {
        return getUniform(name) >= 0;
    }

    void Program::setUniformValue(const UniformKind& kind,
        const UniformValue& value)
    {
        setUniformValue(getUniform(kind), value);
    }

    void Program::setUniformValue(const GLint& location,
        const UniformValue& value)
    {
        use();
        value.set(location);
    }

	const VertexDefinition& Program::getVertexDefinition() const
	{
		return _vertexDefinition;
	}

}
