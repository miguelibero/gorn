#include <gorn/render/TextureManager.hpp>
#include <gorn/render/Texture.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    TextureManager::TextureManager(AssetManager<Image>& images):
    _images(images)
    {
        getDefinitions().set([](const std::string& name){
            return Definition()
                .withImage(name);
        });
    }

    const TextureManager::Definitions& TextureManager::getDefinitions() const
    {
        return _definitions;
    }

    TextureManager::Definitions& TextureManager::getDefinitions()
    {
        return _definitions;
    }

    bool TextureManager::validate(const std::string& name) const
    {
        auto itr = _textures.find(name);
        if(itr != _textures.end())
        {
            return true;
        }
        if(!getDefinitions().has(name))
        {
            return false;
        }
        auto def = getDefinitions().get(name);
        return _images.validate(def.getImageName());
    }

    glm::vec2 TextureManager::loadSize(const std::string& name)
    {
        auto itr = _textures.find(name);
        if(itr != _textures.end())
        {
            return itr->second->getSize();
        }
        auto& def = getDefinitions().get(name);
        auto img = _images.load(def.getImageName()).get();
        return img->getSize();
    }

    std::shared_ptr<Texture> TextureManager::load(const std::string& name)
    {
        auto itr = _textures.find(name);
        if(itr != _textures.end())
        {
            return itr->second;
        }
        auto& def = getDefinitions().get(name);
        auto img = _images.load(def.getImageName()).get();
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
        tex->setImage(*img, def.getLevelOfDetail());
        _textures.insert(itr, {name, tex});
        return tex;
    }

}
