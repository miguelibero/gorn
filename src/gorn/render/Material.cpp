#include <gorn/render/Material.hpp>

namespace gorn
{
	Material::Material(const std::shared_ptr<Program>& program, const std::vector<std::shared_ptr<Texture>>& textures):
	_program(program), _textures(textures)
	{
	}

	const Program& Material::getProgram()
	{
		return *_program;
	}

	const Texture& Material::getTexture(size_t position)
	{
		return *_textures.at(position);
	};

}
