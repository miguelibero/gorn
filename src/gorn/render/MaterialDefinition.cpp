#include <gorn/render/MaterialDefinition.hpp>

namespace gorn
{

	MaterialDefinition::MaterialDefinition(const std::string& program):
	_program(program)
	{
	}

	MaterialDefinition& MaterialDefinition::withTextures(std::initializer_list<std::string> list)
	{
		_textures.insert(_textures.end(), list.begin(), list.end());
		return *this;
	}

	const std::string& MaterialDefinition::getProgram()
	{
		return _program;
	}

	const std::vector<std::string>& MaterialDefinition::getTextures()
	{
		return _textures;
	}

}
