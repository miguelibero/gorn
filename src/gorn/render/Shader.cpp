#include <gorn/render/Shader.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
	Shader::Shader(const Data& source, ShaderType type):
	_id(0)
	{
        GLenum glType = 0;
        if(type == ShaderType::Vertex)
        {
            glType = GL_VERTEX_SHADER;
        }
        else if(type == ShaderType::Fragment)
        {
            glType = GL_FRAGMENT_SHADER;
        }
		_id = glCreateShader(glType);
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
        glDeleteShader(_id);
	}

	GLuint Shader::getId() const
	{
		return _id;
	}
}
