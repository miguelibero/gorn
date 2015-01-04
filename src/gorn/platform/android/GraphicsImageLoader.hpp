
#ifndef __gorn__GraphicsImageLoader__
#define __gorn__GraphicsImageLoader__

#include <gorn/asset/AssetLoader.hpp>

namespace gorn {

    class Image;

    class GraphicsImageLoader : public AssetLoader<Image>
    {
    public:
        bool validate(const Data& input) const;
        Image load(Data&& input) const;
    };
}

#endif
