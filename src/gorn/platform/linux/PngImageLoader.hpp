
#ifndef __gorn__PngImageLoader__
#define __gorn__PngImageLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class Image;

    class PngImageLoader : public AssetLoader<Image>
    {
    public:
        bool validate(const Data& input) const;
        Image load(Data&& input) const;
    };
}

#endif
