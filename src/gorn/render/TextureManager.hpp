#ifndef __gorn__TextureManager__
#define __gorn__TextureManager__

#include <map>
#include <string>
#include <memory>
#include <gorn/render/Gl.hpp>
#include <gorn/render/TextureDefinition.hpp>
#include <gorn/render/Texture.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    class TextureManager
    {
    private:
        std::map<std::string, std::shared_ptr<Texture>> _textures;
        std::map<std::string, TextureDefinition> _definitions;
        
        AssetManager<Image>& _images;

    public:
        static const char* kDefaultTag;

        TextureManager(AssetManager<Image>& images);

        TextureDefinition& define(const std::string& name);
        std::shared_ptr<Texture> load(const std::string& name);

    };
}

#endif
