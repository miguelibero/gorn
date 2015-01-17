

#ifndef __gorn__SpriteDefinition__
#define __gorn__SpriteDefinition__

#include <gorn/sprite/SpriteAnimationDefinition.hpp>
#include <string>
#include <map>

namespace gorn {


    class SpriteDefinition
    {
    public:
        typedef SpriteAnimationDefinition Animation;

    private:
        std::string _atlas;
        std::map<std::string, Animation> _anims;
    public:
        SpriteDefinition();

        SpriteDefinition& withAtlas(const std::string& atlas);
        SpriteDefinition& withAnimation(const std::string& name, const Animation& anim);

        Animation& setAnimation(const std::string& name);

        const std::string& getAtlas() const;

        const Animation& getAnimation(const std::string& name) const;
        bool hasAnimation(const std::string& name) const;
        const std::map<std::string, Animation>& getAnimations() const;
    };

}

#endif
