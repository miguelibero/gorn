
#include <gorn/label/LabelAtlasRegion.hpp>

namespace gorn {

    LabelAtlasRegion::LabelAtlasRegion():
    _advance(0.0f)
    {
    }

    float LabelAtlasRegion::getAdvance() const
    {
        auto sizex = getOriginalSize().x;
        if(sizex < _advance)
        {
            return _advance;
        }
        else
        {
            return sizex;
        }
    }

    void LabelAtlasRegion::setAdvance(float value)
    {
        _advance = value;
    }
}
