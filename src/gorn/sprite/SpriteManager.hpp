

#ifndef __gorn__SpriteManager__
#define __gorn__SpriteManager__

#include <gorn/asset/AssetManager.hpp>
#include <gorn/sprite/SpriteDefinition.hpp>
#include <gorn/render/MaterialDefinition.hpp>

namespace gorn {

    class Sprite;
    class FileManager;
    class MaterialManager;
    class SpriteAtlas;

    class SpriteManager
    {
    public:
        typedef SpriteDefinition Definition;
    private:
        MaterialManager& _materials;
        AssetManager<SpriteAtlas> _atlases;
        std::map<std::string, Definition> _definitions;
        MaterialDefinition _materialdef;
    public:
        SpriteManager(MaterialManager& materials, FileManager& files);

        const AssetManager<SpriteAtlas>& getAtlases() const;
        AssetManager<SpriteAtlas>& getAtlases();

        MaterialDefinition& getDefaultMaterialDefinition();

        SpriteDefinition& define(const std::string& name);

        Sprite load(const std::string& name);
    };

}

#endif
