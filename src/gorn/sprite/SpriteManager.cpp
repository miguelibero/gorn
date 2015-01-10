

#include <gorn/sprite/SpriteManager.hpp>
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/sprite/GdxSpriteAtlasLoader.hpp>
#include <gorn/sprite/Sprite.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/RenderSystem2D.hpp>

namespace gorn {

    SpriteManager::SpriteManager(MaterialManager& materials, FileManager& files):
    _materials(materials), _atlases(files)
    {
        _materialdef.withProgram(RenderSystem2D::Sprite);
        _atlases.addLoader<GdxSpriteAtlasLoader>();
    }
    
    MaterialDefinition& SpriteManager::getDefaultMaterialDefinition()
    {
        return _materialdef;
    }

    const AssetManager<SpriteAtlas>& SpriteManager::getAtlases() const
    {
        return _atlases;
    }

    AssetManager<SpriteAtlas>& SpriteManager::getAtlases()
    {
        return _atlases;
    }

    SpriteDefinition& SpriteManager::define(const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            itr = _definitions.insert(itr, {name, SpriteDefinition()});
            itr->second.withAtlas(name);
        }
        return itr->second;
    }

    Sprite SpriteManager::load(const std::string& name)
    {
        auto& def = define(name);
        Sprite sprite;
        for(auto itr = def.getAnimations().begin();
            itr != def.getAnimations().end(); ++itr)
        {
            std::string atlasName = itr->second.getAtlas();
            if(atlasName.empty())
            {
                atlasName = def.getAtlas();
            }
            auto atlas = _atlases.load(atlasName).get();
            std::string materialName = itr->second.getMaterial();
            if(materialName.empty())
            {
                materialName = def.getMaterial();
            }
            if(materialName.empty())
            {
                materialName = atlas->getMaterial();
            }
            if(!_materials.hasDefined(materialName))
            {
                _materials.define(materialName, _materialdef);
            }
            auto material = _materials.load(materialName);
            auto& anim = sprite.setAnimation(itr->first);
            anim.withMaterial(material);
            anim.withFrameDuration(itr->second.getFrameDuration());
            for(auto& name : itr->second.getFrames())
            {
                anim.addFrames(atlas->getRegions(name));
            }
        }
        return sprite;
    }

}

