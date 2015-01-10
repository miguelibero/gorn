
#ifndef __gorn__GdxSpriteAtlasLoader__
#define __gorn__GdxSpriteAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class SpriteAtlas;

    class GdxSpriteAtlasLoader : public AssetLoader<SpriteAtlas>
    {      
    public:
        GdxSpriteAtlasLoader();

        bool validate(const Data& data) const;
        SpriteAtlas load(Data&& data) const;
    };
}

#endif
