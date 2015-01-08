#include <gorn/render/Program.hpp>
#include <gorn/render/UniformValue.hpp>
#include <gorn/base/Exception.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gorn
{
    GLuint Program::s_currentId = 0;

	Program::Program(const std::shared_ptr<Shader>& fragmentShader, const std::shared_ptr<Shader>& vertexShader):
	_id(0), _fragmentShader(fragmentShader), _vertexShader(vertexShader)
	{
		_id = glCreateProgram();
        glAttachShader(_id, _fragmentShader->getId());
        glAttachShader(_id, _vertexShader->getId());
        glLinkProgram(_id);
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

    GLint Program::loadAttribute(const std::string& name, const std::string& alias)
    {
        auto id = getAttribute(name);
        _attributes[alias] = id;
        return id;
    }

    GLint Program::loadUniform(const std::string& name, const std::string& alias)
    {
        auto id = getUniform(name);
        _uniforms[alias] = id;
        return id;
    }

    GLint Program::getAttribute(const std::string& name) const
    {
        auto itr = _attributes.find(name);
        if(itr == _attributes.end())
        {
            GLint id = glGetAttribLocation(getId(), name.c_str());
            if(id == -1)
            {
                throw Exception(std::string("Could not find attribure '")+name+"'.");
            }
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
            if(id == -1)
            {
                throw Exception(std::string("Could not find uniform '")+name+"'.");
            }
            itr = _uniforms.insert(itr, {name, id});
        }
        return itr->second;
	}

    void Program::setUniformValue(const std::string& name, const UniformValue& value)
    {
        setUniformValue(getUniform(name), value);
    }

	void Program::setUniformValue(const GLint& location, const UniformValue& value)
	{
        value.set(location);
	}

}
