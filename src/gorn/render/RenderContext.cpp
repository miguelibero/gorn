#include <gorn/render/RenderContext.hpp>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#elif GORN_PLATFORM_ANDROID
#include <gorn/platform/android/BundleFileLoader.hpp>
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#endif

namespace gorn
{

    RenderContext::RenderContext():
    _images(_files),
    _vdefs(_files),
    _programs(_files),
    _textures(_images),
    _materials(_programs, _textures),
    _queue(_vdefs, _materials)
    {
    }

    FileManager& RenderContext::getFiles()
    {
        return _files;
    }

    const FileManager& RenderContext::getFiles() const
    {
        return _files;
    }

    AssetManager<Image>& RenderContext::getImages()
    {
        return _images;
    }

    const AssetManager<Image>& RenderContext::getImages() const
    {
        return _images;
    }

    AssetManager<VertexDefinition>& RenderContext::getVertexDefinitions()
    {
        return _vdefs;
    }

    const AssetManager<VertexDefinition>& RenderContext::getVertexDefinitions() const
    {
        return _vdefs;
    }

    RenderQueue& RenderContext::getQueue()
    {
        return _queue;
    }

    const RenderQueue& RenderContext::getQueue() const
    {
        return _queue;
    }

    TextureManager& RenderContext::getTextures()
    {
        return _textures;
    }

    const TextureManager& RenderContext::getTextures() const
    {
        return _textures;
    }

    ProgramManager& RenderContext::getPrograms()
    {
        return _programs;
    }

    const ProgramManager& RenderContext::getPrograms() const
    {
        return _programs;
    }

    MaterialManager& RenderContext::getMaterials()
    {
        return _materials;
    }

    const MaterialManager& RenderContext::getMaterials() const
    {
        return _materials;
    }

    void RenderContext::basicSetup()
    {

#ifdef GORN_PLATFORM_LINUX
		getFiles()
            .addDefaultLoader<LocalFileLoader>("../%s");
		getImages()
            .addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		getFiles()
            .addDefaultLoader<BundleFileLoader>("%s");
		getImages()
            .addLoader<GraphicsImageLoader>();
#endif
    }

}
