
#ifndef __gorn__CocosSpriteAtlasLoader__
#define __gorn__CocosSpriteAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class SpriteAtlas;

    class CocosSpriteAtlasLoader : public AssetLoader<SpriteAtlas>
    {
    public:
        CocosSpriteAtlasLoader();

        bool validate(const Data& data) const;
        SpriteAtlas load(Data&& data) const;

    };
}

#endif
