#ifndef __gorn__Context__
#define __gorn__Context__

#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/TextureManager.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    class Image;
    class Application;

    class Context
    {
    private:
        FileManager _files;
        AssetManager<Image> _images;
        ProgramManager _programs;
        TextureManager _textures;
        MaterialManager _materials;
        RenderQueue _queue;
    public:

        Context();

        FileManager& getFiles();
        const FileManager& getFiles() const;

        AssetManager<Image>& getImages();
        const AssetManager<Image>& getImages() const;

        RenderQueue& getQueue();
        const RenderQueue& getQueue() const;

        TextureManager& getTextures();
        const TextureManager& getTextures() const;

        ProgramManager& getPrograms();
        const ProgramManager& getPrograms() const;

        MaterialManager& getMaterials();
        const MaterialManager& getMaterials() const;

        template<typename T>
        AssetManager<T> createAssetManager();

        void reload();
    };

    template<typename T>
    AssetManager<T> Context::createAssetManager()
    {
        return AssetManager<T>(getFiles());
    }

}

#endif
