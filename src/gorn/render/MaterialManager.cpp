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

    bool MaterialManager::validate(const std::string& name) const
    {
        auto itr = _materials.find(name);
        if(itr != _materials.end())
        {
            return true;
        }
        auto def = getDefinitions().get(name);
        auto& pname = def.getProgram();
        if(!_programs.validate(pname))
        {
            return false;
        }
        for(auto itr = def.getTextures().begin();
            itr != def.getTextures().end(); ++itr)
        {
            if(!_textures.validate(itr->second))
            {
                return false;
            }
        }
        return true;
    }

    glm::vec2 MaterialManager::loadSize(const std::string& name)
    {
        auto itr = _materials.find(name);
        if(itr != _materials.end())
        {
            return itr->second->getSize();
        }
        auto& def = getDefinitions().get(name);
        if(def.getTextures().empty())
        {
            return glm::vec2(0.0f);
        }
        else
        {
            auto& tdef = def.getTextures().begin()->second;
            return _textures.loadSize(tdef);
        }
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
        for(auto itr = pdef.getUniforms().begin();
            itr != pdef.getUniforms().end(); ++itr)
        {
            if(!itr->second.value.empty())
            {
                material->setUniformValue(itr->first, itr->second.value);
            }
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
