

#ifndef __gorn__Sprite__
#define __gorn__Sprite__

#include <gorn/sprite/SpriteAnimation.hpp>

namespace gorn {

    class RenderQueue;

    class Sprite
    {
    public:
        typedef SpriteAnimation Animation;
        static const char* kDefaultAnimation;
    private:
        std::map<std::string, Animation> _anims;
        std::string _currentAnim;
    public:
        Sprite();
        Sprite(const Animation& anim);
        Sprite(const std::shared_ptr<Material>& material);
        Sprite(const std::shared_ptr<Material>& material, const SpriteAtlasRegion& region);

        void setAnimation(const std::string& name, const Animation& anim);
        Animation& setAnimation(const std::string& name);

        void play(const std::string& name);

        void update(double dt);
        void render(RenderQueue& queue) const;
    };

}

#endif
