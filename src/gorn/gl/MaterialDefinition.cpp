#include <gorn/gl/MaterialDefinition.hpp>

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
        const std::string& name)
    {
        return withTexture(name, name);
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
