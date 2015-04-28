
#ifndef __gorn__PngImageLoader__
#define __gorn__PngImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn {

    class Image;

    class PngImageLoader : public DataAssetLoader<Image>
    {
    public:
        bool validate(const buffer& input) const NOEXCEPT override;
        Image load(const buffer& input) const override;
    };
}

#endif
