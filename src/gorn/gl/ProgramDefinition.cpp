#include <gorn/gl/ProgramDefinition.hpp>
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

	ProgramDefinition& ProgramDefinition::withUniform(const Uniform& uniform)
	{
		_uniforms.push_back(uniform);
		return *this;
	}

    ProgramDefinition& ProgramDefinition::withAttribute(
        const Attribute& attribute)
    {
		_attributes.push_back(attribute);
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
		for (auto& udef : _uniforms)
		{
			values[udef.getKind()] = udef.getDefaultValue();
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
		for (auto& adef : _attributes)
		{
			auto offset = vdef.getElementSize();
			vdef.setAttribute(adef.getKind())
				.withBasicType(adef.getBasicType())
				.withCount(adef.getCount())
				.withOffset(offset)
				.withDefaultValue(adef.getDefaultValue())
				.withTransformation(adef.getTransformation());
		}

		size_t stride = vdef.getElementSize();
		for (auto& adef : vdef.getAttributes())
		{
			adef.withStride(stride);
		}
		return vdef;
	}

}
