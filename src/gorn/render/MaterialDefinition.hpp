#ifndef __gorn__MaterialDefinition__
#define __gorn__MaterialDefinition__

#include <gorn/render/Gl.hpp>
#include <gorn/render/UniformValue.hpp>
#include <string>
#include <map>
#include <initializer_list>

namespace gorn
{
	class MaterialDefinition
	{
	private:
		std::string _program;
		std::map<std::string, std::string> _textures;
		std::map<std::string, UniformValue> _uniformValues;

	public:
		MaterialDefinition();
        MaterialDefinition& withProgram(const std::string& program);
		MaterialDefinition& withTexture(const std::string& name, const std::string& value);
		MaterialDefinition& withTexture(const std::string& name);        
		MaterialDefinition& withUniformValue(const std::string& name, const UniformValue& value);

		const std::string& getProgram() const;
		const std::map<std::string, std::string>& getTextures() const;
		const std::map<std::string, UniformValue>& getUniformValues() const;
	};

}

#endif
