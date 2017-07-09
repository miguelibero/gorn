#include <gorn/gl/MaterialDefinition.hpp>
#include <gorn/base/Exception.hpp>
namespace gorn
{

    MaterialDefinition::MaterialDefinition()
    {
    }

    MaterialDefinition& MaterialDefinition::withProgram(
        const std::string& program)
    {
        _program = program;
        return *this;
    }

    MaterialDefinition& MaterialDefinition::withTexture(
        const UniformKind& kind, const std::string& value)
    {
        _textures[kind] = value;
        return *this;
    }

    MaterialDefinition& MaterialDefinition::withUniformValue(
        const UniformKind& kind, const UniformValue& value)
    {
        _uniformValues[kind] = value;
        return *this;
    }

    const std::string& MaterialDefinition::getProgram() const
    {
        return _program;
    }

    const MaterialDefinition::Textures&
        MaterialDefinition::getTextures() const
    {
        return _textures;
    }

    const UniformValueMap&
        MaterialDefinition::getUniformValues() const
    {
        return _uniformValues;
    }

	MaterialDefinition::Textures& MaterialDefinition::getTextures()
	{
		return _textures;
	}

	UniformValueMap& MaterialDefinition::getUniformValues()
	{
		return _uniformValues;
	}

}
