

#ifndef __gorn__SpriteAnimationFrame__
#define __gorn__SpriteAnimationFrame__

#include <memory>
#include <gorn/base/Data.hpp>
#include <gorn/sprite/SpriteAtlasRegion.hpp>

namespace gorn {

    class RenderQueue;
    class Material;

    class SpriteAnimationFrame
    {
    public:
        typedef SpriteAtlasRegion Region;
    private:
        std::shared_ptr<Material> _material;
        SpriteAtlasRegion _region;
        bool _dirty;

        mutable Data _texVerts;
        mutable Data _posVerts;
        mutable Data _elmVerts;

        void updateElementData();
        void updatePositionData();
        void updateTextureData();

    public:
        SpriteAnimationFrame();
        explicit SpriteAnimationFrame(const std::shared_ptr<Material>& material);
        SpriteAnimationFrame(const std::shared_ptr<Material>& material, const Region& region);

        void setMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Material>& getMaterial() const;

        void setRegion(const Region& region);
        const Region& getRegion() const;
        
        void update();
        void render(RenderQueue& queue) const;
    };

}

#endif
