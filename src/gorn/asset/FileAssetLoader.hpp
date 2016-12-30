#ifndef __gorn__FileAssetLoader__
#define __gorn__FileAssetLoader__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <unordered_map>
#include <gorn/asset/AssetLoader.hpp>
#include <gorn/asset/DataAssetLoader.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/base/String.hpp>

namespace gorn
{
    template<typename T>
    class FileAssetLoader : public AssetLoader<T>
    {
    public:
        typedef DataAssetLoader<T> Loader;
        typedef std::vector<std::shared_ptr<Loader>> Loaders;
    private:
        FileManager& _files;
        Loaders _defaultLoaders;
        std::unordered_map<std::string, Loaders> _loaders;
        std::unordered_map<std::string, Loaders> _customLoaders;

        Loaders getLoaders(const std::string& name) const NOEXCEPT;

    public:
        FileAssetLoader(FileManager& files) NOEXCEPT;

        virtual bool validate(const std::string& name) const NOEXCEPT override;
        virtual T load(const std::string& name) const override;

        void addDefaultLoader(std::unique_ptr<Loader>&& loader) NOEXCEPT;
        void addLoader(const std::string& tag,
            std::unique_ptr<Loader>&& loader) NOEXCEPT;
        void addCustomLoader(const std::string& name,
            std::unique_ptr<Loader>&& loader) NOEXCEPT;

        template<typename L, typename... Args>
        void makeDefaultLoader(Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        void makeLoader(const std::string& tag, Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        void makeCustomLoader(const std::string& name, Args&&... args) NOEXCEPT;
    };

    template<typename T>
    FileAssetLoader<T>::FileAssetLoader(FileManager& files) NOEXCEPT:
    _files(files)
    {
    }

    template<typename T>
    void FileAssetLoader<T>::addDefaultLoader(
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader == nullptr)
        {
            return;
        }
        _defaultLoaders.push_back(std::move(loader));
    }

    template<typename T>
    void FileAssetLoader<T>::addLoader(const std::string& tag,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader == nullptr)
        {
            return;
        }
        _loaders[tag].push_back(std::move(loader));
    }

    template<typename T>
    void FileAssetLoader<T>::addCustomLoader(const std::string& name,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader == nullptr)
        {
            return;
        }
        _customLoaders[name].push_back(std::move(loader));
    }

    template<typename T>
    template<typename L, typename... Args>
    void FileAssetLoader<T>::makeDefaultLoader(Args&&... args) NOEXCEPT
    {
        addDefaultLoader(std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
    template<typename L, typename... Args>
    void FileAssetLoader<T>::makeLoader(const std::string& tag,
        Args&&... args) NOEXCEPT
    {
        addLoader(tag, std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
    template<typename L, typename... Args>
    void FileAssetLoader<T>::makeCustomLoader(const std::string& name,
        Args&&... args) NOEXCEPT
    {
        addLoader(name, std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
    typename FileAssetLoader<T>::Loaders FileAssetLoader<T>::getLoaders(
        const std::string& name) const NOEXCEPT
    {
        Loaders loaders;
        auto itr = _customLoaders.find(name);
        if(itr != _customLoaders.end())
        {
            for(auto& loader : itr->second)
            {
                loaders.push_back(loader);
            }
        }
        auto parts = String::splitTag(name);
        itr = _loaders.find(parts.first);
        if(itr != _loaders.end())
        {
            for(auto& loader : itr->second)
            {
                loaders.push_back(loader);
            }
        }
        loaders.insert(loaders.end(),
            _defaultLoaders.begin(), _defaultLoaders.end());
        return loaders;
    }

    template<typename T>
    bool FileAssetLoader<T>::validate(const std::string& name) const NOEXCEPT
    {
        auto loaders = getLoaders(name);
        try
        {
            auto data = _files.load(name, true).get();
            for(auto& loader : loaders)
            {
                if(loader->validate(data))
                {
                    return true;
                }
            }
        }
        catch(const Exception&)
        {
        }
        return false;
    }

    template<typename T>
    T FileAssetLoader<T>::load(const std::string& name) const
    {
        auto loaders = getLoaders(name);
        auto data = _files.load(name, true).get();
        for(auto& loader : loaders)
        {
            if(loader->validate(data))
            {
                try
                {
                    return loader->load(data);
                }
                catch(const Exception&)
                {
                }
            }
        }
        throw Exception("Could not load asset.");
    }

}

#endif
