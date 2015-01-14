

#include <gorn/sprite/SpriteManager.hpp>
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/sprite/GdxSpriteAtlasLoader.hpp>
#include <gorn/sprite/FntSpriteAtlasLoader.hpp>
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

    const SpriteManager::FrameList& SpriteManager::loadFrames(
        const std::string& aname, const std::string& fname)
    {
        auto atlas = _atlases.load(aname).get();
        auto& frames = _frames[aname];
        auto fitr = frames.find(fname);
        if(fitr == frames.end())
        {
            fitr = frames.insert(fitr, std::make_pair(fname, FrameList()));
            auto& regions = atlas->getRegions(fname);
            fitr->second.reserve(regions.size());
            for(auto& region : regions)
            {
                std::string mname = atlas->getMaterial(region.getPage());
                if(!_materials.hasDefined(mname))
                {
                    _materials.define(mname, _materialdef);
                }
                auto material = _materials.load(mname);
                fitr->second.push_back(std::make_shared<SpriteFrame>(
                    material, region));                
            }
        }
        return fitr->second;
    }

    Sprite SpriteManager::load(const std::string& dname)
    {
        auto& def = define(dname);
        Sprite sprite;
        for(auto itr = def.getAnimations().begin();
            itr != def.getAnimations().end(); ++itr)
        {
            auto& anim = sprite.setAnimation(itr->first);
            anim.withFrameDuration(itr->second.getFrameDuration());
            std::string aname = itr->second.getAtlas();
            if(aname.empty())
            {
                aname = def.getAtlas();
            }
            for(auto& fname : itr->second.getFrames())
            {
                anim.withFrames(loadFrames(aname, fname));
            }
        }
        return sprite;
    }

}

