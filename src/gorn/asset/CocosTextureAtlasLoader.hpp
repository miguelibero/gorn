
#ifndef __gorn__CocosTextureAtlasLoader__
#define __gorn__CocosTextureAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class TextureAtlas;

    class CocosTextureAtlasLoader : public AssetLoader<TextureAtlas>
    {
    public:
        CocosTextureAtlasLoader();

        bool validate(const Data& data) const;
        TextureAtlas load(Data&& data) const;

    };
}

#endif
