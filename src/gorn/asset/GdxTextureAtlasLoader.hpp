
#ifndef __gorn__GdxTextureAtlasLoader__
#define __gorn__GdxTextureAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class TextureAtlas;

    class GdxTextureAtlasLoader : public AssetLoader<TextureAtlas>
    {      
    public:
        GdxTextureAtlasLoader();

        bool validate(const Data& data) const;
        TextureAtlas load(Data&& data) const;
    };
}

#endif
