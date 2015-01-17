

#include <gorn/sprite/SpriteManager.hpp>
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/sprite/Sprite.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/render/MaterialManager.hpp>

namespace gorn {

    SpriteManager::SpriteManager(MaterialManager& materials, FileManager& files):
    _materials(materials), _atlases(files)
    {
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
            itr = _definitions.insert(itr, {name, Definition()});
            itr->second.withAtlas(name);
        }
        return itr->second;
    }

    const SpriteManager::FrameList& SpriteManager::loadFrames(
        const std::string& aname, const std::string& fname)
    {
        return loadFrames(aname).at(fname);
    }

    const SpriteManager::FrameMap& SpriteManager::loadFrames(
            const std::string& aname)
    {
        auto itr = _frames.find(aname);
        if(itr == _frames.end())
        {
            itr = _frames.insert(itr, std::make_pair(aname, FrameMap()));
            auto& frames = itr->second;
            auto atlas = _atlases.load(aname).get();
            auto& regions = atlas->getRegions();
            for(auto ritr = regions.begin(); ritr != regions.end(); ++ritr)
            {
                auto& fname = ritr->first;
                auto fitr = frames.find(fname);
                if(fitr == frames.end())
                {
                    fitr = frames.insert(fitr, std::make_pair(fname, FrameList()));
                    fitr->second.reserve(ritr->second.size());
                    for(auto& region : ritr->second)
                    {
                        std::string mname = atlas->getMaterial(region.getPage());
                        auto material = _materials.load(mname);
                        fitr->second.push_back(std::make_shared<SpriteFrame>(
                            material, region));
                    }

                }
            }
        }

        return itr->second;
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

