#include <gorn/render/Program.hpp>

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
}