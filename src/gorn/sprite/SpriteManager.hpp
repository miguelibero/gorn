

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
        typedef std::vector<std::shared_ptr<SpriteFrame>> FrameList;
        typedef std::map<std::string, FrameList> FrameMap;
    private:
        MaterialManager& _materials;
        AssetManager<SpriteAtlas> _atlases;
        std::map<std::string, Definition> _definitions;
        std::map<std::string, FrameMap> _frames;
    public:
        SpriteManager(MaterialManager& materials, FileManager& files);

        const AssetManager<SpriteAtlas>& getAtlases() const;
        AssetManager<SpriteAtlas>& getAtlases();

        SpriteDefinition& define(const std::string& name);

        Sprite load(const std::string& name);

        const FrameList& loadFrames(
            const std::string& aname, const std::string& fname);

        const FrameMap& loadFrames(
            const std::string& aname);

    };

}

#endif
