

#ifndef __gorn__SpriteFrame__
#define __gorn__SpriteFrame__

#include <memory>
#include <glm/glm.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/sprite/SpriteAtlasRegion.hpp>

namespace gorn {

    class RenderQueue;
    class Material;

    class SpriteFrame
    {
    public:
        typedef SpriteAtlasRegion Region;
    private:
        std::shared_ptr<Material> _material;
        SpriteAtlasRegion _region;

        bool _dirtyTexVerts;
        bool _dirtyPosVerts;
        bool _dirtyElmVerts;

        mutable Data _texVerts;
        mutable Data _posVerts;
        mutable Data _elmVerts;

        void updateElementData();
        void updatePositionData();
        void updateTextureData();

        void init();

    public:
        SpriteFrame();
        explicit SpriteFrame(const std::shared_ptr<Material>& material);
        SpriteFrame(const std::shared_ptr<Material>& material, const Region& region);

        void setMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Material>& getMaterial() const;

        void setRegion(const Region& region);
        const Region& getRegion() const;

        void update();
        void render(RenderQueue& queue) const;
    };

}

#endif
