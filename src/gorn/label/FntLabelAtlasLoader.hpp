
#ifndef __gorn__FntLabelAtlasLoader__
#define __gorn__FntLabelAtlasLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class LabelAtlas;

    class FntLabelAtlasLoader : public AssetLoader<LabelAtlas>
    {
    public:
        FntLabelAtlasLoader();
        bool validate(const Data& data) const;
        LabelAtlas load(Data&& data) const;
          
    };
}

#endif
