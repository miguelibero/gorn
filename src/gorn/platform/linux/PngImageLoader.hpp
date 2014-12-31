
#ifndef __gorn__PngImageLoader__
#define __gorn__PngImageLoader__

#include <gorn/platform/ImageLoader.hpp>

namespace gorn {

    class PngImageLoader : public ImageLoader
    {
    public:
        bool validate(const Data& input) const;
        std::future<Image> load(Data&& input) const;
    };
}

#endif
