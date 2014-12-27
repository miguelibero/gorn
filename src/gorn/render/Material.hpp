#ifndef __gorn__Material__
#define __gorn__Material__

#include <gorn/render/Program.hpp>
#include <gorn/render/Texture.hpp>

namespace gorn
{
	class Material
	{
	private:
		std::shared_ptr<Program> _program;
		std::vector<std::shared_ptr<Texture>> _textures;

	public:
		Material(const std::shared_ptr<Program>& program, const std::vector<std::shared_ptr<Texture>>& textures);

		const Program& getProgram();
		const Texture& getTexture(size_t position);
	};

}

#endif