#ifndef __gorn__RenderSystem2D__
#define __gorn__RenderSystem2D__

#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    class RenderContext;
    class SpriteAtlas;

    class RenderSystem2D
    {
    private:
        RenderContext& _context;
        AssetManager<SpriteAtlas> _spriteAtlases;
    public:
        static const char* Sprite;

        RenderSystem2D(RenderContext& context);
        
        const AssetManager<SpriteAtlas>& getSpriteAtlases() const;
        AssetManager<SpriteAtlas>& getSpriteAtlases();
    };
}

#endif
