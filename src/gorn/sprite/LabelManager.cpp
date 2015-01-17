
#include <gorn/sprite/LabelManager.hpp>
#include <gorn/sprite/Label.hpp>
#include <gorn/sprite/SpriteManager.hpp>

namespace gorn {
    
    LabelManager::LabelManager(MaterialManager& materials, FileManager& files):
    _sprites(materials, files)
    {
    }

    const AssetManager<SpriteAtlas>& LabelManager::getAtlases() const
    {
        return _sprites.getAtlases();
    }

    AssetManager<SpriteAtlas>& LabelManager::getAtlases()
    {
        return _sprites.getAtlases();
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

    Label LabelManager::load(const std::string& name)
    {
        auto& def = define(name);
        auto& frames = _sprites.loadFrames(def.getAtlas());
        SpriteFont font;
        for(auto itr=frames.begin(); itr!=frames.end(); ++itr)
        {
            if(!itr->second.empty())
            {
                font.setLetter(itr->first, itr->second.front());
            }
        }
        return Label(font);
    }
}

