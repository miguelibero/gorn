#include <gorn/gl/MaterialDefinition.hpp>
#include <gorn/render/RenderKinds.hpp>
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
        const std::string& name, const std::string& value)
    {
        _textures[name] = value;
        return *this;
    }

    MaterialDefinition& MaterialDefinition::withTexture(
        const std::string& value)
    {
        return withTexture(UniformKind::Texture0, value);
    }

	MaterialDefinition& MaterialDefinition::withTexture(
		unsigned int pos, const std::string& value)
	{
		std::string name;
		switch(pos)
		{
		case 0:
			name = UniformKind::Texture0;
			break;
		case 1:
			name = UniformKind::Texture1;
			break;
		case 2:
			name = UniformKind::Texture2;
			break;
		case 3:
			name = UniformKind::Texture3;
			break;
		case 4:
			name = UniformKind::Texture4;
			break;
		case 5:
			name = UniformKind::Texture5;
			break;
		case 6:
			name = UniformKind::Texture6;
			break;
		default:
			throw Exception("Texture position not supported.");
		}
		return withTexture(name, value);
	}

    MaterialDefinition& MaterialDefinition::withUniformValue(
        const std::string& name, const UniformValue& value)
    {
        _uniformValues[name] = value;
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

}
