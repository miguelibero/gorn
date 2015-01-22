

#ifndef __gorn__LabelManager__
#define __gorn__LabelManager__

#include <gorn/label/LabelDefinition.hpp>
#include <gorn/label/LabelFont.hpp>
#include <gorn/asset/AssetManager.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <map>

namespace gorn {
    
    class Label;
    class LabelAtlas;
    class MaterialManager;
    class FileManager;

    class LabelManager
    {
    public:
        typedef LabelDefinition Definition;
        typedef LabelAtlas Atlas;
        typedef LabelFont Font;
        typedef AssetManager<Atlas> AtlasManager;
    private:
        MaterialManager& _materials;
        AtlasManager _atlases;
        std::map<std::string, std::shared_ptr<Font>> _fonts;
        std::map<std::string, Definition> _definitions;
    public:
        LabelManager(MaterialManager& materials, FileManager& files);

        const AtlasManager& getAtlases() const;
        AtlasManager& getAtlases();

        std::shared_ptr<Font> loadFont(const std::string& name);

        Definition& define(const std::string& name);
        Label load(const std::string& name);
    };

}

#endif
