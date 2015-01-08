#ifndef __gorn__ProgramDefinition__
#define __gorn__ProgramDefinition__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Shader.hpp>
#include <string>
#include <map>
#include <initializer_list>

namespace gorn
{
    class AttributeKind
    {
    private:
        AttributeKind();
    public:
        static const char* Position;
        static const char* Color;
        static const char* TexCoords;
    };

    class UniformKind
    {
    private:
        UniformKind();
    public:
        static const char* Texture0;
        static const char* Texture1;
        static const char* Texture2;
        static const char* Texture3;
        static const char* Texture4;
        static const char* Texture5;
        static const char* Texture6;
        static const char* Color;
    };

	class ProgramDefinition
	{
	private:
		std::map<ShaderType, std::string> _shaderFiles;
        std::map<ShaderType, Data> _shaderData;
		std::map<std::string, std::string> _uniforms;
		std::map<std::string, std::string> _attributes;

	public:
		ProgramDefinition();
        ProgramDefinition& withShaderFile(ShaderType type, const std::string& name);
        ProgramDefinition& withShaderData(ShaderType type, Data&& data);
        ProgramDefinition& withShaderData(ShaderType type, const std::string& data);
        ProgramDefinition& withUniform(const std::string& name, const std::string& alias);
        ProgramDefinition& withUniform(const std::string& name);
		ProgramDefinition& withAttribute(const std::string& name);
		ProgramDefinition& withAttribute(const std::string& name, const std::string& alias);
    
        bool hasShaderData(ShaderType type) const;
        const Data& getShaderData(ShaderType type) const;
        bool hasShaderFile(ShaderType type) const;
		const std::string& getShaderFile(ShaderType type) const;
		const std::map<std::string, std::string>& getUniforms() const;
		const std::map<std::string, std::string>& getAttributes() const;
	};

}

#endif
