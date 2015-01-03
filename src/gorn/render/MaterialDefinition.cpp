#include <gorn/render/MaterialDefinition.hpp>

namespace gorn
{

	MaterialDefinition::MaterialDefinition()
	{
	}

    MaterialDefinition& MaterialDefinition::withProgram(const std::string& program)
    {
        _program = program;
        return *this;
    }

	MaterialDefinition& MaterialDefinition::withTexture(const std::string& uniform, const std::string& name)
    {
        _textures[uniform] = name;
		return *this;
    }

	MaterialDefinition& MaterialDefinition::withTexture(const std::string& name)
    {
        return withTexture(name, name);
    }

	const std::string& MaterialDefinition::getProgram() const
	{
		return _program;
	}

	const std::map<std::string, std::string>& MaterialDefinition::getTextures() const
	{
		return _textures;
	}

}
