

#ifndef __gorn__LabelManager__
#define __gorn__LabelManager__

#include <gorn/sprite/LabelDefinition.hpp>
#include <gorn/sprite/SpriteManager.hpp>
#include <map>

namespace gorn {
    
    class Label;
    class MaterialManager;
    class FileManager;

    class LabelManager
    {
    public:
        typedef LabelDefinition Definition;
    private:
        SpriteManager _sprites;
        std::map<std::string, Definition> _definitions;
    public:
        LabelManager(MaterialManager& materials, FileManager& files);

        const AssetManager<SpriteAtlas>& getAtlases() const;
        AssetManager<SpriteAtlas>& getAtlases();

        Definition& define(const std::string& name);
        Label load(const std::string& name);
    };

}

#endif
