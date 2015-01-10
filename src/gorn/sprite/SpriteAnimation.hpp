

#ifndef __gorn__SpriteAnimation__
#define __gorn__SpriteAnimation__

#include <gorn/render/Material.hpp>
#include <gorn/sprite/SpriteAtlasRegion.hpp>
#include <memory>

namespace gorn {

    class SpriteAnimation
    {
    public:
        typedef SpriteAtlasRegion Frame;
    private:
        std::shared_ptr<Material> _material;
        std::vector<Frame> _frames;
        double _frameDuration;

    public:
        SpriteAnimation();
        SpriteAnimation(const std::shared_ptr<Material>& material);
        SpriteAnimation(const std::shared_ptr<Material>& material, const Frame& frame);
        
        SpriteAnimation& withMaterial(const std::shared_ptr<Material>& material);
        SpriteAnimation& withFrameDuration(double duration);
        SpriteAnimation& addFrame(const Frame& frame);
        SpriteAnimation& addFrames(const std::vector<Frame>& frames);

        const std::shared_ptr<Material>& getMaterial() const;
        const Frame& getFrame(double pos) const;
        double getTotalDuration() const;
    };

}

#endif
