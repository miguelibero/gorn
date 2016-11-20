#ifndef __gorn__ProgramDefinition__
#define __gorn__ProgramDefinition__

#include <gorn/gl/Base.hpp>
#include <gorn/gl/Shader.hpp>
#include <gorn/gl/ProgramAttributeDefinition.hpp>
#include <gorn/gl/ProgramUniformDefinition.hpp>
#include <string>
#include <vector>

class buffer;

namespace gorn
{
	class VertexDefinition;

    class ProgramDefinition
    {
    public:
        typedef ProgramAttributeDefinition Attribute;
        typedef ProgramUniformDefinition Uniform;
        typedef std::vector<Uniform> Uniforms;
        typedef std::vector<Attribute> Attributes;
    private:
        std::unordered_map<ShaderType, std::string> _shaderFiles;
        std::unordered_map<ShaderType, buffer> _shaderData;
        Uniforms _uniforms;
        Attributes _attributes;
    public:
        ProgramDefinition();
        ProgramDefinition& withShaderFile(ShaderType type,
            const std::string& name);
        ProgramDefinition& withShaderData(ShaderType type, buffer&& data);
        ProgramDefinition& withShaderData(ShaderType type,
            const std::string& data);

		ProgramDefinition& withUniform(const Uniform& uniform);
        ProgramDefinition& withAttribute(const Attribute& attribute);

        bool hasShaderData(ShaderType type) const;
        const buffer& getShaderData(ShaderType type) const;
        bool hasShaderFile(ShaderType type) const;
        const std::string& getShaderFile(ShaderType type) const;
        const Uniforms& getUniforms() const;
		UniformValueMap getUniformValues() const;
        const Attributes& getAttributes() const;
		VertexDefinition getVertexDefinition() const;
    };

}

#endif
