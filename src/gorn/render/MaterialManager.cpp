#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/TextureManager.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/Material.hpp>
#include <gorn/render/Kinds.hpp>

namespace gorn
{
    MaterialManager::MaterialManager(
        ProgramManager& programs, TextureManager& textures):
    _programs(programs),
    _textures(textures)
    {
        getDefinitions().set([](const std::string& name){
            return Definition()
                .withTexture(UniformKind::Texture0, name);
        });
    }

    const MaterialManager::Definitions& MaterialManager::getDefinitions() const
    {
        return _definitions;
    }

    MaterialManager::Definitions& MaterialManager::getDefinitions()
    {
        return _definitions;
    }


    std::shared_ptr<Material> MaterialManager::load(const std::string& name)
    {
        auto itr = _materials.find(name);
        if(itr != _materials.end())
        {
            return itr->second;
        }
        auto& def = getDefinitions().get(name);
        auto& pname = def.getProgram();
        auto program = _programs.load(pname);
        auto material = std::make_shared<Material>(program);
        for(auto itr = def.getTextures().begin();
            itr != def.getTextures().end(); ++itr)
        {
            material->setTexture(itr->first, _textures.load(itr->second));
        }
        auto& pdef = _programs.getDefinitions().get(pname);
        for(auto itr = pdef.getUniformValues().begin();
            itr != pdef.getUniformValues().end(); ++itr)
        {
            material->setUniformValue(itr->first, itr->second);
        }
        for(auto itr = def.getUniformValues().begin();
            itr != def.getUniformValues().end(); ++itr)
        {
            material->setUniformValue(itr->first, itr->second);
        }

        _materials.insert(itr, {name, material});
        return material;
    }

}
