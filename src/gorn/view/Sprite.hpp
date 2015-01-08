

#ifndef __gorn__Sprite__
#define __gorn__Sprite__

#include <gorn/asset/SpriteRegion.hpp>
#include <gorn/render/Material.hpp>
#include <memory>

namespace gorn {

    class RenderQueue;
    class TextureRegion;

    class Sprite
    {
    public:
        typedef SpriteRegion Region;
    private:
        std::shared_ptr<Material> _material;
        Region _region;
        bool _dirty;
        Data _positionData;
        Data _texcoordsData;
        Data _elementsData;

        void init();
    public:
        Sprite(const std::shared_ptr<Material>& material=nullptr);
        Sprite(const std::shared_ptr<Material>& material, const Region& region);

        void setMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Material>& getMaterial() const;

        const Region& getRegion() const;
        void setRegion(const Region& region);

        void render(RenderQueue& queue);
    };

}

#endif
