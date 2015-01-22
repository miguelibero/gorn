

#ifndef __gorn__LabelDefinition__
#define __gorn__LabelDefinition__

#include <string>

namespace gorn {


    class LabelDefinition
    {
    private:
        std::string _material;
        std::string _atlas;
    public:
        LabelDefinition();

        LabelDefinition& withAtlas(const std::string& atlas);

        const std::string& getAtlas() const;
    };

}

#endif
