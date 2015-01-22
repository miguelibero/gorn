#ifndef __gorn__ProgramDefinition__
#define __gorn__ProgramDefinition__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Shader.hpp>
#include <gorn/render/UniformValue.hpp>
#include <string>
#include <map>

namespace gorn
{

	class ProgramDefinition
	{
    public:
        typedef std::map<std::string, std::string> Uniforms;
        typedef std::map<std::string, std::string> Attributes;
        typedef std::map<std::string, UniformValue> UniformValues;
	private:
		std::map<ShaderType, std::string> _shaderFiles;
        std::map<ShaderType, Data> _shaderData;
		Uniforms _uniforms;
		Attributes _attributes;
		UniformValues _uniformValues;
	public:
		ProgramDefinition();
        ProgramDefinition& withShaderFile(ShaderType type,
            const std::string& name);
        ProgramDefinition& withShaderData(ShaderType type, Data&& data);
        ProgramDefinition& withShaderData(ShaderType type,
            const std::string& data);
        ProgramDefinition& withUniform(const std::string& name,
            const std::string& alias);
        ProgramDefinition& withUniform(const std::string& name);
		ProgramDefinition& withAttribute(const std::string& name);
		ProgramDefinition& withAttribute(const std::string& name,
            const std::string& alias);
  		ProgramDefinition& withUniformValue(const std::string& name,
            const UniformValue& value);

        bool hasShaderData(ShaderType type) const;
        const Data& getShaderData(ShaderType type) const;
        bool hasShaderFile(ShaderType type) const;
		const std::string& getShaderFile(ShaderType type) const;
		const Uniforms& getUniforms() const;
		const Attributes& getAttributes() const;
		const UniformValues& getUniformValues() const;
	};

}

#endif
