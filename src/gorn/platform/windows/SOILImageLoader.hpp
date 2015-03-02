
#ifndef __gorn__SOILImageLoader__
#define __gorn__SOILImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn {

    class Image;

	class SOILImageLoader : public DataAssetLoader<Image>
    {
    public:
        bool validate(const Data& input) const;
        Image load(Data&& input) const;
    };
}

#endif
