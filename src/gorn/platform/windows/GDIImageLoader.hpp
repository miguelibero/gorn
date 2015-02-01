
#ifndef __gorn__ImagingImageLoader__
#define __gorn__ImagingImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn {

    class Image;

	class GDIImageLoader : public DataAssetLoader<Image>
    {
    public:
        bool validate(const Data& input) const;
        Image load(Data&& input) const;
    };
}

#endif
