#ifndef __gorn__TextureManager__
#define __gorn__TextureManager__

#include <map>
#include <memory>
#include <functional>
#include <gorn/base/DefinitionManager.hpp>
#include <gorn/render/TextureDefinition.hpp>
#include <gorn/asset/Image.hpp>

namespace gorn
{
    class Texture;

    template<typename T>
    class AssetManager;

    class TextureManager
    {
    public:
        typedef TextureDefinition Definition;
        typedef DefinitionManager<TextureDefinition> Definitions;
    private:
        std::map<std::string, std::shared_ptr<Texture>> _textures;
        AssetManager<Image>& _images;
        Definitions _definitions;

    public:
        TextureManager(AssetManager<Image>& images);

        const Definitions& getDefinitions() const;
        Definitions& getDefinitions();

        std::shared_ptr<Texture> load(const std::string& name);

    };
}

#endif
