#include <gorn/render/Shader.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
	Shader::Shader(const Data& source, GLenum type):
	_id(0)
	{
		_id = glCreateShader(type);
		auto ptr = (const GLchar*)source.data();
		auto size = (const GLint)source.size();
        glShaderSource(_id, 1, &ptr, &size);
        glCompileShader(_id);
        GLint status;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
        if(status != GL_TRUE)
        {
            char buffer[512];
            glGetShaderInfoLog(_id, sizeof(buffer), NULL, buffer);
            throw Exception(buffer);
        }
	}

	Shader::~Shader()
	{

	}

	GLuint Shader::getId() const
	{
		return _id;
	}
}