

#ifndef __gorn__LabelCharacter__
#define __gorn__LabelCharacter__

#include <gorn/sprite/SpriteFrame.hpp>
#include <gorn/label/LabelAtlasRegion.hpp>

namespace gorn {

    class LabelCharacter : public SpriteFrame
    {
    public:
        typedef LabelAtlasRegion Region;
    private:
        bool _dirty;
        glm::mat4 _transform;
        Region _region;
        SpriteFrame _frame;

        void init();

    public:
        LabelCharacter();
        explicit LabelCharacter(const std::shared_ptr<Material>& material);
        LabelCharacter(const std::shared_ptr<Material>& material, const Region& region);

        void setRegion(const Region& region);
        const Region& getRegion() const;

        void update();
        void render(RenderQueue& queue) const;

    };

}

#endif
