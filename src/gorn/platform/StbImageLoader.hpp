
#ifndef __gorn__StbImageLoader__
#define __gorn__StbImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn {

    class Image;

    class StbImageLoader : public DataAssetLoader<Image>
    {
    public:
        StbImageLoader() NOEXCEPT;
        bool validate(const buffer& input) const NOEXCEPT override;
        Image load(const buffer& input) const override;
    };
}

#endif
