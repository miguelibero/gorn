#ifndef __gorn__TextureManager__
#define __gorn__TextureManager__

#include <map>
#include <memory>
#include <functional>
#include <gorn/base/DefinitionManager.hpp>
#include <gorn/gl/TextureDefinition.hpp>
#include <gorn/asset/Image.hpp>
#include <glm/glm.hpp>

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

        std::shared_ptr<Texture> doLoad(const std::string& name);
    public:
        TextureManager(AssetManager<Image>& images);

        const Definitions& getDefinitions() const;
        Definitions& getDefinitions();

        bool validate(const std::string& name) const;
        std::shared_ptr<Texture> load(const std::string& name);
        glm::vec2 loadSize(const std::string& name);
		void load(const std::string& name, const std::shared_ptr<Texture>& tex);
        void reload();

    };
}

#endif
