
#ifndef __gorn__GdxSpriteAtlasLoader__
#define __gorn__GdxSpriteAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class SpriteAtlas;
    class MaterialManager;

    class GdxSpriteAtlasLoader : public AssetLoader<SpriteAtlas>
    {      
    private:
        MaterialManager& _materials;
    public:
        GdxSpriteAtlasLoader(MaterialManager& materials);

        bool validate(const Data& data) const;
        SpriteAtlas load(Data&& data) const;
    };
}

#endif
