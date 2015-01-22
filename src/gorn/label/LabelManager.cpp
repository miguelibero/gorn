
#include <gorn/label/LabelManager.hpp>
#include <gorn/label/Label.hpp>
#include <gorn/label/LabelAtlas.hpp>
#include <gorn/render/MaterialManager.hpp>

namespace gorn {
    
    LabelManager::LabelManager(MaterialManager& materials, FileManager& files):
    _materials(materials), _atlases(files)
    {
    }

    const LabelManager::AtlasManager& LabelManager::getAtlases() const
    {
        return _atlases;
    }

    LabelManager::AtlasManager& LabelManager::getAtlases()
    {
        return _atlases;
    }

    LabelManager::Definition& LabelManager::define(const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            itr = _definitions.insert(itr, {name, Definition()});
            itr->second.withAtlas(name);
        }
        return itr->second;
    }

    std::shared_ptr<LabelManager::Font> LabelManager::loadFont(const std::string& name)
    {
        auto itr = _fonts.find(name);
        if(itr == _fonts.end())
        {
            auto atlas = _atlases.load(name).get();
            auto font = std::make_shared<Font>();
            for(auto ritr=atlas->getRegions().begin();
                ritr!=atlas->getRegions().end(); ++ritr)
            {
                auto& region = ritr->second;
                std::string mname = atlas->getMaterial(region.getPage());
                auto material = _materials.load(mname);
                Font::Character chr(material, region);
                font->setCharacter(ritr->first, chr);
            }
            itr = _fonts.insert(itr, {name, font});
        }
        return itr->second;
    }

    Label LabelManager::load(const std::string& name)
    {
        auto& def = define(name);
        return Label(loadFont(def.getAtlas()));
    }
}

