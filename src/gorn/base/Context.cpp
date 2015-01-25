#include <gorn/base/Context.hpp>

namespace gorn
{

    Context::Context():
    _images(_files),
    _programs(_files),
    _textures(_images),
    _materials(_programs, _textures),
    _queue(_materials)
    {
    }

    FileManager& Context::getFiles()
    {
        return _files;
    }

    const FileManager& Context::getFiles() const
    {
        return _files;
    }

    AssetManager<Image>& Context::getImages()
    {
        return _images;
    }

    const AssetManager<Image>& Context::getImages() const
    {
        return _images;
    }

    RenderQueue& Context::getQueue()
    {
        return _queue;
    }

    const RenderQueue& Context::getQueue() const
    {
        return _queue;
    }

    TextureManager& Context::getTextures()
    {
        return _textures;
    }

    const TextureManager& Context::getTextures() const
    {
        return _textures;
    }

    ProgramManager& Context::getPrograms()
    {
        return _programs;
    }

    const ProgramManager& Context::getPrograms() const
    {
        return _programs;
    }

    MaterialManager& Context::getMaterials()
    {
        return _materials;
    }

    const MaterialManager& Context::getMaterials() const
    {
        return _materials;
    }

}
