#include <gorn/gl/ProgramDefinition.hpp>
#include <gorn/render/RenderKinds.hpp>
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

    ProgramDefinition& ProgramDefinition::withAttribute(
        const std::string& alias,
        const Attribute& attribute)
    {
        _attributes[alias] = attribute;
        if(AttributeKind::isTransformable(alias))
        {
            _attributes[alias].transformable = true;
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

    const ProgramDefinition::Attributes& ProgramDefinition::
        getAttributes() const
    {
        return _attributes;
    }

}
