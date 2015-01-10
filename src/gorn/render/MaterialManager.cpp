#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/TextureManager.hpp>
#include <gorn/render/Kinds.hpp>

namespace gorn
{
    MaterialManager::MaterialManager(ProgramManager& programs, TextureManager& textures):
    _programs(programs),
    _textures(textures)
    {
    }

    void MaterialManager::setDefaultProgram(const std::string& program)
    {
        _defaultProgram = program;
    }

    std::shared_ptr<Material> MaterialManager::load(const std::string& name)
    {
        auto itr = _materials.find(name);
        if(itr != _materials.end())
        {
            return itr->second;
        }
        auto& def = define(name);
        auto progname = def.getProgram();
        if(progname.empty())
        {
            progname = _defaultProgram;
        }
        auto program = _programs.load(progname);
        auto material = std::make_shared<Material>(program);
        for(auto itr = def.getTextures().begin();
            itr != def.getTextures().end(); ++itr)
        {
            material->setTexture(itr->first, _textures.load(itr->second));
        }
        for(auto itr = def.getUniformValues().begin();
            itr != def.getUniformValues().end(); ++itr)
        {
            material->setUniformValue(itr->first, itr->second);
        }

        _materials.insert(itr, {name, material});
        return material;
    }

    MaterialDefinition& MaterialManager::define(const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            itr = _definitions.insert(itr, {name, MaterialDefinition()});
            itr->second.withTexture(UniformKind::Texture0, name);
        }
        return itr->second;
    }
}
