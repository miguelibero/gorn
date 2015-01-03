#include <gorn/render/RenderContext.hpp>

namespace gorn
{

    RenderContext::RenderContext():
    _images(_files),
    _programs(_files),
    _textures(_images),
    _materials(_programs, _textures)
    {
    }

    FileManager& RenderContext::getFileManager()
    {
        return _files;
    }

    const FileManager& RenderContext::getFileManager() const
    {
        return _files;
    }

    AssetManager<Image>& RenderContext::getImageManager()
    {
        return _images;
    }

    const AssetManager<Image>& RenderContext::getImageManager() const
    {
        return _images;
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

}
