#include <gorn/render/Program.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/UniformValue.hpp>
#include <gorn/render/Kinds.hpp>
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
        glAttachShader(_id, _vertexShader->getId());
        glLinkProgram(_id);

        checkGlError("linking a program");
	}

	Program::~Program()
	{
        glDeleteProgram(_id);
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
        for(auto itr = def.getAttributes().begin();
            itr != def.getAttributes().end(); ++itr)
        {
            auto id = getAttribute(itr->second.name);
            _attributes[itr->first] = id;
            _transformableAttributes[itr->first]
                 = itr->second.transformable;
        }
        for(auto itr = def.getUniforms().begin();
            itr != def.getUniforms().end(); ++itr)
        {
            auto id = getUniform(itr->second.name);
            _uniforms[itr->first] = id;
            if(!itr->second.value.empty())
            {
                setUniformValue(id, itr->second.value);
            }
        }
    }

    GLint Program::getAttribute(const std::string& name) const
    {
        auto itr = _attributes.find(name);
        if(itr == _attributes.end())
        {
            GLint id = glGetAttribLocation(getId(), name.c_str());
            itr = _attributes.insert(itr, {name, id});
        }
        return itr->second;
    }

	GLint Program::getUniform(const std::string& name) const
	{
        auto itr = _uniforms.find(name);
        if(itr == _uniforms.end())
        {
		    GLint id = glGetUniformLocation(getId(), name.c_str());
            itr = _uniforms.insert(itr, {name, id});
        }
        return itr->second;
	}

    bool Program::hasTransformableAttribute(const std::string& name) const
    {
        auto itr = _transformableAttributes.find(name);
        if(itr != _transformableAttributes.end())
        {
            return itr->second;
        }
        if(AttributeKind::isTransformable(name) && hasAttribute(name))
        {
            return true;
        }
        return false;
    }

    bool Program::hasAttribute(const std::string& name) const
    {
        return getAttribute(name) >= 0;
    }

    bool Program::hasUniform(const std::string& name) const
    {
        return getUniform(name) >= 0;
    }

    void Program::setUniformValue(const std::string& name,
        const UniformValue& value)
    {
        setUniformValue(getUniform(name), value);
    }

	void Program::setUniformValue(const GLint& location,
        const UniformValue& value)
	{
        if(location >= 0)
        {
            use();
            value.set(location);
        }
	}

}
