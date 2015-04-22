#ifndef __gorn__MaterialDefinition__
#define __gorn__MaterialDefinition__

#include <gorn/gl/GlBase.hpp>
#include <gorn/gl/UniformValue.hpp>
#include <string>
#include <map>

namespace gorn
{
	class MaterialDefinition
	{
    public:
        typedef std::map<std::string, std::string> Textures;
        typedef std::map<std::string, UniformValue> UniformValues;
	private:
		std::string _program;
		Textures _textures;
		UniformValues _uniformValues;

	public:
		MaterialDefinition();
        MaterialDefinition& withProgram(
            const std::string& program);
		MaterialDefinition& withTexture(
            const std::string& name, const std::string& value);
		MaterialDefinition& withTexture(
            const std::string& name);        
		MaterialDefinition& withUniformValue(
            const std::string& name, const UniformValue& value);

		const std::string& getProgram() const;
		const Textures& getTextures() const;
		const UniformValues& getUniformValues() const;
	};

}

#endif
