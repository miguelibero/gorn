#include <gorn/render/ProgramDefinition.hpp>

namespace gorn
{

	ProgramDefinition::ProgramDefinition()
    {
    }

    ProgramDefinition& ProgramDefinition::withShaderFile(ShaderType type, const std::string& name)
    {
        _shaderFiles[type] = name;
        return *this;
    }

    ProgramDefinition& ProgramDefinition::withShaderData(ShaderType type, Data&& data)
    {
        _shaderData[type] = std::move(data);
        return *this;
    }

    ProgramDefinition& ProgramDefinition::withShaderData(ShaderType type, const std::string& data)
    {
        return withShaderData(type, Data(data));
    }

    ProgramDefinition& ProgramDefinition::withUniform(
        const std::string& name)
    {
        return withUniform(name, name);
    }

    ProgramDefinition& ProgramDefinition::withUniform(
        const std::string& name, const std::string& alias)
    {
        _uniforms[alias] = name;
        return *this;
    }

    ProgramDefinition& ProgramDefinition::withAttribute(
        const std::string& name)
    {
        return withAttribute(name, name);
    }

    ProgramDefinition& ProgramDefinition::withAttribute(
        const std::string& name, const std::string& alias)
    {
        _attributes[alias] = name;
        return *this;
    }

    ProgramDefinition& ProgramDefinition::withUniformValue(
        const std::string& name, const UniformValue& value)
    {
        _uniformValues[name] = value;
		return *this;
    }

    bool ProgramDefinition::hasShaderData(ShaderType type) const
    {
        auto itr = _shaderData.find(type);
        return itr != _shaderData.end();
    }

    const Data& ProgramDefinition::getShaderData(ShaderType type) const
    {
        return _shaderData.at(type);
    }

    bool ProgramDefinition::hasShaderFile(ShaderType type) const
    {
        auto itr = _shaderFiles.find(type);
        return itr != _shaderFiles.end();
    }

	const std::string& ProgramDefinition::getShaderFile(ShaderType type) const
    {
        return _shaderFiles.at(type);
    }

	const std::map<std::string, std::string>& ProgramDefinition::getUniforms() const
	{
		return _uniforms;
	}

	const std::map<std::string, std::string>& ProgramDefinition::getAttributes() const
	{
		return _attributes;
	}

	const std::map<std::string, UniformValue>& ProgramDefinition::getUniformValues() const
    {
        return _uniformValues;
    }

}
