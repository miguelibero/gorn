
#ifndef __gorn__FntSpriteAtlasLoader__
#define __gorn__FntSpriteAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class SpriteAtlas;

    class FntSpriteAtlasLoader : public AssetLoader<SpriteAtlas>
    {
    public:
        FntSpriteAtlasLoader();
        bool validate(const Data& data) const;
        SpriteAtlas load(Data&& data) const;
          
    };
}

#endif
