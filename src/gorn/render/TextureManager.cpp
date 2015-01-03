#include <gorn/render/TextureManager.hpp>
#include <gorn/asset/Image.hpp>

namespace gorn
{
    const char* TextureManager::kDefaultTag = "tex";

    TextureManager::TextureManager(AssetManager<Image>& images):
    _images(images)
    {
    }

    std::shared_ptr<Texture> TextureManager::load(const std::string& name)
    {
        auto itr = _textures.find(name);
        if(itr != _textures.end())
        {
            return itr->second;
        }
        auto& def = define(name);
        auto img = _images.load(def.getImageTag(), def.getImageName()).get();
        auto tex = std::make_shared<Texture>(def.getTarget());
        for(auto itr = def.getIntParameters().begin();
            itr != def.getIntParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        for(auto itr = def.getFloatParameters().begin();
            itr != def.getFloatParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        for(auto itr = def.getIntPointerParameters().begin();
            itr != def.getIntPointerParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        for(auto itr = def.getFloatPointerParameters().begin();
            itr != def.getFloatPointerParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        tex->setImage(img, def.getLevelOfDetail());
        _textures.insert(itr, {name, tex});
        return tex;
    }

    TextureDefinition& TextureManager::define(const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            itr = _definitions.insert(itr, {name, TextureDefinition()});
            itr->second.withImage(name).withImageTag(kDefaultTag);
        }
        return itr->second;
    }
}
