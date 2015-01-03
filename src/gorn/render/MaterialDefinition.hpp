#ifndef __gorn__MaterialDefinition__
#define __gorn__MaterialDefinition__

#include <gorn/render/Gl.hpp>
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

	public:
		MaterialDefinition();
        MaterialDefinition& withProgram(const std::string& program);
		MaterialDefinition& withTexture(const std::string& uniform, const std::string& name);
		MaterialDefinition& withTexture(const std::string& name);
        
        template<typename V>
		MaterialDefinition& withUniform(const std::string& name, const V& value);

		const std::string& getProgram() const;
		const std::map<std::string, std::string>& getTextures() const;
	};

}

#endif
