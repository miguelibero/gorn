#ifndef __gorn__RenderSystem2D__
#define __gorn__RenderSystem2D__

#include <gorn/asset/AssetManager.hpp>
#include <gorn/sprite/SpriteManager.hpp>
#include <gorn/label/LabelManager.hpp>

namespace gorn
{
    class RenderContext;
    class SpriteAtlas;

    class RenderSystem2D
    {
    private:
        RenderContext& _context;
        SpriteManager _sprites;
        LabelManager _labels;
    public:
        static const char* Sprite;

        RenderSystem2D(RenderContext& context);

        const SpriteManager& getSprites() const;
        SpriteManager& getSprites();

        const LabelManager& getLabels() const;
        LabelManager& getLabels();
    };
}

#endif
