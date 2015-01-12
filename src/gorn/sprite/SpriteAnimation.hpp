

#ifndef __gorn__SpriteAnimation__
#define __gorn__SpriteAnimation__

#include <gorn/render/Material.hpp>
#include <gorn/sprite/SpriteAnimationFrame.hpp>
#include <memory>

namespace gorn {

    class RenderQueue;

    class SpriteAnimation
    {
    public:
        typedef SpriteAnimationFrame Frame;
    private:
        std::vector<Frame> _frames;
        double _frameDuration;
        double _time;

        void init();
    public:
        SpriteAnimation();
        SpriteAnimation(const std::shared_ptr<Material>& material);
        SpriteAnimation(const std::shared_ptr<Material>& material, const SpriteAtlasRegion& region);
        SpriteAnimation(const Frame& frame);
        
        SpriteAnimation& withFrameDuration(double duration);
        SpriteAnimation& addFrame(const Frame& frame);
        SpriteAnimation& addFrame(const std::shared_ptr<Material>& material);
        SpriteAnimation& addFrame(
            const std::shared_ptr<Material>& material,
            const SpriteAtlasRegion& region);

        size_t getCurrentFrameNumber() const;
        const Frame& getCurrentFrame() const;
        Frame& getCurrentFrame();
        
        double getCurrentTime() const;
        double getDuration() const;

        void update(double dt);
        void render(RenderQueue& queue) const;
    };

}

#endif
