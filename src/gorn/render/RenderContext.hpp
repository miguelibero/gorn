#ifndef __gorn__RenderContext__
#define __gorn__RenderContext__

#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/TextureManager.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    class VertexArray;

    class RenderContext
    {
    private:
        FileManager _files;
        AssetManager<Image> _images;
        ProgramManager _programs;
        TextureManager _textures;
        MaterialManager _materials;
        RenderQueue _queue;
    public:

        RenderContext();

        FileManager& getFileManager();
        const FileManager& getFileManager() const;

        AssetManager<Image>& getImageManager();
        const AssetManager<Image>& getImageManager() const;

        RenderQueue& getQueue();
        const RenderQueue& getQueue() const;

        TextureManager& getTextures();
        const TextureManager& getTextures() const;

        ProgramManager& getPrograms();
        const ProgramManager& getPrograms() const;

        MaterialManager& getMaterials();
        const MaterialManager& getMaterials() const;

        template<typename T>
        AssetManager<T> createAssetManager() const;
    };

    template<typename T>
    AssetManager<T> RenderContext::createAssetManager() const
    {
        return AssetManager<T>(getFileManager());
    }
}

#endif
