#include <gorn/render/Program.hpp>
#include <gorn/base/Exception.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gorn
{
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
        glUseProgram(getId());
    }

    GLint Program::getAttribute(const std::string& name) const
    {
        GLint id = glGetAttribLocation(getId(), name.c_str());
        if(id == -1)
        {
            throw Exception(std::string("Could not find attribure '")+name+"'.");
        }
        return id;
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

	void Program::setUniform(const GLint& uniform, int value)
	{
		glUniform1i(uniform, value);
	}

	void Program::setUniform(const GLint& uniform, float value)
	{
		glUniform1f(uniform, value);
	}

	void Program::setUniform(const GLint& uniform, const glm::vec2& value)
	{
		glUniform2f(uniform, value.x, value.y);
	}

	void Program::setUniform(const GLint& uniform, const glm::vec3& value)
	{
		glUniform3f(uniform, value.x, value.y, value.z);
	}

	void Program::setUniform(const GLint& uniform, const glm::vec4& value)
	{
		glUniform4f(uniform, value.x, value.y, value.z, value.w);
	}

	void Program::setUniform(const GLint& uniform, const std::vector<float>& values)
	{
		glUniform1fv(uniform, values.size(), 
            reinterpret_cast<const GLfloat*>(values.data()));
	}

	void Program::setUniform(const GLint& uniform, const std::vector<glm::vec2>& values)
	{
		glUniform2fv(uniform, values.size(),
            reinterpret_cast<const GLfloat*>(values.data()));
	}

	void Program::setUniform(const GLint& uniform, const std::vector<glm::vec3>& values)
	{
		glUniform3fv(uniform, values.size(), 
            reinterpret_cast<const GLfloat*>(values.data()));
	}

	void Program::setUniform(const GLint& uniform, const std::vector<glm::vec4>& values)
	{
		glUniform4fv(uniform, values.size(), 
            reinterpret_cast<const GLfloat*>(values.data()));
	}

	void Program::setUniform(const GLint& uniform, const glm::mat3& value)
	{
		glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Program::setUniform(const GLint& uniform, const glm::mat4& value)
	{
		glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
	}
}
