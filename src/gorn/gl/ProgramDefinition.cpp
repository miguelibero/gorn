#include <gorn/gl/ProgramDefinition.hpp>
#include <gorn/render/RenderKinds.hpp>
#include <gorn/gl/VertexDefinition.hpp>
#include <buffer.hpp>

namespace gorn
{

    ProgramDefinition::ProgramDefinition()
    {
    }

    ProgramDefinition& ProgramDefinition::withShaderFile(
        ShaderType type, const std::string& name)
    {
        _shaderFiles[type] = name;
        return *this;
    }

    ProgramDefinition& ProgramDefinition::withShaderData(
        ShaderType type, buffer&& data)
    {
        _shaderData[type] = std::move(data);
        return *this;
    }

    ProgramDefinition& ProgramDefinition::withShaderData(
        ShaderType type, const std::string& data)
    {
        return withShaderData(type, buffer(data.data(), data.size()));
    }

    ProgramDefinition& ProgramDefinition::withUniform(
        const std::string& alias,
        const Uniform& uniform)
    {
        _uniforms[alias] = uniform;
        return *this;
    }

	ProgramDefinition& ProgramDefinition::withUniform(const Uniform& uniform)
	{
		return withUniform(uniform.getName(), uniform);
	}

    ProgramDefinition& ProgramDefinition::withAttribute(
        const std::string& alias,
        const Attribute& attribute)
    {
        _attributes[alias] = attribute;
		auto itr = _attributes.find(alias);
		if(itr == _attributes.end())
		{
			itr = _attributes.insert(itr, { alias, attribute });
		}
		else
		{
			itr->second = attribute;
		}
		if(itr->second.getTransformation() == nullptr)
		{
			itr->second.withTransformation(AttributeTransformation::create(alias));
		}
        return *this;
    }

    bool ProgramDefinition::hasShaderData(ShaderType type) const
    {
        auto itr = _shaderData.find(type);
        return itr != _shaderData.end();
    }

    const buffer& ProgramDefinition::getShaderData(ShaderType type) const
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

    const ProgramDefinition::Uniforms& ProgramDefinition::getUniforms() const
    {
        return _uniforms;
    }

	UniformValueMap ProgramDefinition::getUniformValues() const
	{
		UniformValueMap values;
		for (auto itr = _uniforms.begin(); itr != _uniforms.end(); ++itr)
		{
			values[itr->first] = itr->second.getDefaultValue();
		}
		return values;
	}

    const ProgramDefinition::Attributes& ProgramDefinition::
        getAttributes() const
    {
        return _attributes;
    }

	VertexDefinition ProgramDefinition::getVertexDefinition() const
	{
		VertexDefinition vdef;
		for (auto itr = _attributes.begin(); itr != _attributes.end(); ++itr)
		{
			auto offset = vdef.getElementSize();
			auto& adef = itr->second;
			vdef.setAttribute(itr->first)
				.withName(adef.getName())
				.withType(adef.getType())
				.withCount(adef.getCount())
				.withOffset(offset)
				.withDefaultValue(adef.getDefaultValue())
				.withTransformation(adef.getTransformation());
		}

		size_t stride = vdef.getElementSize();
		for (auto itr = vdef.getAttributes().begin();
			itr != vdef.getAttributes().end(); ++itr)
		{
			itr->second.withStride(stride);
		}
		return vdef;
	}

}
