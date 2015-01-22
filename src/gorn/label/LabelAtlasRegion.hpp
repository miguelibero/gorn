

#ifndef __gorn__LabelAtlasRegion__
#define __gorn__LabelAtlasRegion__

#include <gorn/sprite/SpriteAtlasRegion.hpp>

namespace gorn {

    class LabelAtlasRegion : public SpriteAtlasRegion
    {

    private:
        float _advance;

    public:
        LabelAtlasRegion();

        float getAdvance() const;
        void setAdvance(float value);
    };

}

#endif
