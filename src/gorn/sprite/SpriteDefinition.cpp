
#include <gorn/sprite/SpriteDefinition.hpp>

namespace gorn {

    SpriteDefinition::SpriteDefinition()    
    {
    }

    SpriteDefinition& SpriteDefinition::withAtlas(const std::string& atlas)
    {
        _atlas = atlas;
        return *this;
    }

    SpriteDefinition& SpriteDefinition::withAnimation(const std::string& name,
        const SpriteDefinition::Animation& anim)
    {
        _anims[name] = anim;
        return *this;
    }

    SpriteDefinition::Animation& SpriteDefinition::setAnimation(const std::string& name)
    {
        auto itr = _anims.find(name);
        if(itr == _anims.end())
        {
            itr = _anims.insert(itr, {name, Animation()});
        }
        return itr->second;
    }

    const std::string& SpriteDefinition::getAtlas() const
    {
        return _atlas;
    }

    const SpriteDefinition::Animation& SpriteDefinition::getAnimation(const std::string& name) const
    {
        return _anims.at(name);
    }

    bool SpriteDefinition::hasAnimation(const std::string& name) const
    {
        return _anims.find(name) != _anims.end();
    }

    const std::map<std::string, SpriteDefinition::Animation>& SpriteDefinition::getAnimations() const
    {
        return _anims;
    }

}
