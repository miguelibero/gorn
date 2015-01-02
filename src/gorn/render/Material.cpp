#include <gorn/render/Material.hpp>

namespace gorn
{
	Material::Material(const std::shared_ptr<Program>& program,
        const std::map<std::string, std::shared_ptr<Texture>>& textures):
	_program(program)
	{
        for(auto itr = textures.begin();
            itr != textures.end(); ++itr)
        {
            _textures[_program->getUniform(itr->first)] = itr->second;
        }
	}

	const std::shared_ptr<Program>& Material::getProgram() const
	{
		return _program;
	}

    void Material::activate()
    {
        _program->use();
        size_t i = 0;
        for(auto itr = _textures.begin();
            itr != _textures.end(); ++itr)
        {
            _program->setUniform(itr->first, (int)i);
            itr->second->activate(i);
            ++i;
        }
    }


}
