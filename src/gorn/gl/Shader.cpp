#include <gorn/gl/Shader.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>

namespace gorn
{
	Shader::Shader(const buffer& source, ShaderType type):
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
        if(_id == 0)
        {
            throw Exception("Could not create shader.");
        }
		auto ptr = (const GLchar*)source.data();
		auto size = (const GLint)source.size();
        glShaderSource(_id, 1, &ptr, &size);
        glCompileShader(_id);
        GLint status;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
        if((GLenum)status == GL_FALSE)
        {
            char buffer[512];
            glGetShaderInfoLog(_id, sizeof(buffer), NULL, buffer);
            if(buffer[0] == 0)
            {
                throw Exception("Could not compile shader.");
            }
            throw Exception(buffer);
        }
	}

	Shader::~Shader()
	{
        if(glIsShader(_id) == GL_TRUE)
        {
            glDeleteShader(_id);
            checkGlError("deleting shader");
        }
	}

	GLuint Shader::getId() const
	{
		return _id;
	}
}
