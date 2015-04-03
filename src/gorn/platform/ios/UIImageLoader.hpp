
#ifndef __gorn__UIImageLoader__
#define __gorn__UIImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn {

    class Image;

    class UIImageLoader : public DataAssetLoader<Image>
    {
    public:
        bool validate(const buffer& input) const NOEXCEPT;
        Image load(const buffer& input) const;
    };
}

#endif
