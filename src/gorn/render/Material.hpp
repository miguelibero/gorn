#ifndef __gorn__Material__
#define __gorn__Material__

#include <gorn/render/Program.hpp>
#include <gorn/render/Texture.hpp>
#include <map>

namespace gorn
{
	class Material
	{
	private:
		std::shared_ptr<Program> _program;
		std::map<GLint, std::shared_ptr<Texture>> _textures;

	public:
		Material(const std::shared_ptr<Program>& program,
            const std::map<std::string, std::shared_ptr<Texture>>& textures);

		const Program& getProgram() const;
		Program& getProgram();
        void use();
	};

}

#endif
