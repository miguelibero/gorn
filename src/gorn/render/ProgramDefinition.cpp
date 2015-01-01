#include <gorn/render/ProgramDefinition.hpp>

namespace gorn
{
	
	ProgramDefinition::ProgramDefinition()
    {
    }

    ProgramDefinition& ProgramDefinition::withShader(const std::string& shader)
    {
        _vertexShader = shader;
        _fragmentShader = shader;
		return *this;
    }

    ProgramDefinition& ProgramDefinition::withVertexShader(const std::string& shader)
    {
        _vertexShader = shader;
		return *this;
    }

    ProgramDefinition& ProgramDefinition::withFragmentShader(const std::string& shader)
    {
        _fragmentShader = shader;
		return *this;
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
