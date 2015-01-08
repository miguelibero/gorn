
#ifndef __gorn__CocosSpriteAtlasLoader__
#define __gorn__CocosSpriteAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class SpriteAtlas;
    class MaterialManager;

    class CocosSpriteAtlasLoader : public AssetLoader<SpriteAtlas>
    {
    private:
        MaterialManager& _materials;
    public:
        CocosSpriteAtlasLoader(MaterialManager& materials);

        bool validate(const Data& data) const;
        SpriteAtlas load(Data&& data) const;

    };
}

#endif
