

#ifndef __gorn__SpriteManager__
#define __gorn__SpriteManager__

#include <gorn/asset/AssetManager.hpp>
#include <gorn/sprite/SpriteDefinition.hpp>

namespace gorn {

    class Sprite;
    class FileManager;
    class MaterialManager;
    class SpriteAtlas;
    class SpriteFrame;

    class SpriteManager
    {
    public:
        typedef SpriteDefinition Definition;
        typedef SpriteAtlas Atlas;
        typedef std::vector<std::shared_ptr<SpriteFrame>> FrameList;
        typedef std::map<std::string, FrameList> FrameMap;
        typedef AssetManager<Atlas> AtlasManager;
    private:
        MaterialManager& _materials;
        AtlasManager _atlases;
        std::map<std::string, Definition> _definitions;
        std::map<std::string, FrameMap> _frames;
    public:
        SpriteManager(MaterialManager& materials, FileManager& files);

        const AtlasManager& getAtlases() const;
        AtlasManager& getAtlases();

        SpriteDefinition& define(const std::string& name);

        Sprite load(const std::string& name);

        const FrameList& loadFrames(
            const std::string& aname, const std::string& fname);

        const FrameMap& loadFrames(
            const std::string& aname);

    };

}

#endif
