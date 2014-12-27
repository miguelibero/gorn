#ifndef __gorn__MaterialDefinition__
#define __gorn__MaterialDefinition__

#include <gorn/render/Gl.hpp>
#include <string>
#include <vector>
#include <initializer_list>

namespace gorn
{
	class MaterialDefinition
	{
	private:
		std::string _program;
		std::vector<std::string> _textures;

	public:
		MaterialDefinition(const std::string& program);
		MaterialDefinition& withTextures(std::initializer_list<std::string> list);

		const std::string& getProgram();
		const std::vector<std::string>& getTextures();
	};

}

#endif