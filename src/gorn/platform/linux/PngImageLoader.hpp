
#ifndef __gorn__PngImageLoader__
#define __gorn__PngImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn {

    class Image;

    class PngImageLoader : public DataAssetLoader<Image>
    {
    public:
        bool validate(const Data& input) const NOEXCEPT;
        Image load(const Data& input) const;
    };
}

#endif
