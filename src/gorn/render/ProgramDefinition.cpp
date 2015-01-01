#include <gorn/render/ProgramDefinition.hpp>

namespace gorn
{
	
	ProgramDefinition::ProgramDefinition(const std::string& shader):
	_vertexShader(shader), _fragmentShader(shader)
	{
	}

	ProgramDefinition::ProgramDefinition(const std::string& vertexShader, const std::string& fragmentShader):
	_vertexShader(vertexShader), _fragmentShader(fragmentShader)
	{
	}

	ProgramDefinition& ProgramDefinition::withUniforms(std::initializer_list<std::string> list)
	{
		_uniforms.insert(_uniforms.end(), list.begin(), list.end());
		return *this;
	}

	ProgramDefinition& ProgramDefinition::withAttributes(std::initializer_list<std::string> list)
	{
		_attributes.insert(_attributes.end(), list.begin(), list.end());
		return *this;
	}

	const std::string& ProgramDefinition::getVertexShader() const
	{
		return _vertexShader;
	}

	const std::string& ProgramDefinition::getFragmentShader() const
	{
		return _fragmentShader;
	}

	const std::vector<std::string> ProgramDefinition::getUniforms() const
	{
		return _uniforms;
	}

	const std::vector<std::string> ProgramDefinition::getAttributes() const
	{
		return _attributes;
	}

}
