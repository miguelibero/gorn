#ifndef __gorn__AssetManager__
#define __gorn__AssetManager__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <unordered_map>
#include <gorn/base/Config.hpp>
#include <gorn/asset/AssetLoader.hpp>
#include <gorn/asset/FileAssetLoader.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/base/String.hpp>

namespace gorn
{
    template<typename T>
    class AssetManager
    {
    public:
        typedef AssetLoader<T> Loader;
        typedef DataAssetLoader<T> DataLoader;
        typedef FileAssetLoader<T> FileLoader;
        typedef std::vector<std::shared_ptr<Loader>> Loaders;
        typedef std::unordered_map<std::string, std::shared_ptr<T>> Assets;
    private:
        std::shared_ptr<FileLoader> _files;
        Loaders _defaultLoaders;
        std::unordered_map<std::string, Loaders> _loaders;
        std::unordered_map<std::string, Loaders> _customLoaders;
        std::shared_ptr<Assets> _assets;

        Loaders getLoaders(const std::string& name) const NOEXCEPT;

        std::future<std::shared_ptr<T>> load(
            const std::shared_ptr<Loader>& loader,
            const std::string& name, bool cache);

    public:
        AssetManager(FileManager& files) NOEXCEPT;

        bool validate(const std::string& name) const NOEXCEPT;

        std::future<std::shared_ptr<T>> load(
            const std::string& name, bool cache=false) NOEXCEPT;

        T& preload(const std::string& name,
            const std::shared_ptr<T>& asset) NOEXCEPT;

        template<typename... Args>
        T& makePreload(const std::string& name, Args&&... args) NOEXCEPT;

        void addDefaultLoader(std::unique_ptr<Loader>&& loader) NOEXCEPT;
        void addLoader(const std::string& tag,
            std::unique_ptr<Loader>&& loader) NOEXCEPT;
        void addCustomLoader(const std::string& name,
            std::unique_ptr<Loader>&& loader) NOEXCEPT;

        template<typename L, typename... Args>
        L& makeDefaultLoader(Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        L& makeLoader(const std::string& tag, Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        L& makeCustomLoader(const std::string& name, Args&&... args) NOEXCEPT;

        void addDefaultDataLoader(
            std::unique_ptr<DataLoader>&& loader) NOEXCEPT;
        void addDataLoader(const std::string& tag,
            std::unique_ptr<DataLoader>&& loader) NOEXCEPT;
        void addCustomDataLoader(const std::string& name,
            std::unique_ptr<DataLoader>&& loader) NOEXCEPT;

        template<typename L, typename... Args>
        L& makeDefaultDataLoader(Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        L& makeDataLoader(const std::string& tag, Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        L& makeCustomDataLoader(const std::string& name, Args&&... args) NOEXCEPT;

        bool remove(const std::shared_ptr<T>& asset) NOEXCEPT;
        bool remove(const std::string& name) NOEXCEPT;
        void clear() NOEXCEPT;
    };

    template<typename T>
    AssetManager<T>::AssetManager(FileManager& files) NOEXCEPT:
    _files(std::make_shared<FileLoader>(files)),
    _assets(std::make_shared<Assets>())
    {
    }

    template<typename T>
    void AssetManager<T>::addDefaultLoader(
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
        _defaultLoaders.push_back(std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addLoader(const std::string& tag,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
        _loaders[tag].push_back(std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addCustomLoader(const std::string& name,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
        _customLoaders[name].push_back(std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addDefaultDataLoader(
        std::unique_ptr<DataLoader>&& loader) NOEXCEPT
    {
        _files->addDefaultLoader(std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addDataLoader(const std::string& tag,
        std::unique_ptr<DataLoader>&& loader) NOEXCEPT
    {
        _files->addLoader(tag, std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addCustomDataLoader(const std::string& name,
        std::unique_ptr<DataLoader>&& loader) NOEXCEPT
    {
        _files->addCustomLoader(name, std::move(loader));
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::makeDefaultLoader(Args&&... args) NOEXCEPT
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addDefaultLoader(std::unique_ptr<Loader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::makeLoader(
        const std::string& tag, Args&&... args) NOEXCEPT
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addLoader(tag, std::unique_ptr<Loader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::makeCustomLoader(
        const std::string& name, Args&&... args) NOEXCEPT
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addCustomLoader(name, std::unique_ptr<Loader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::makeDefaultDataLoader(Args&&... args) NOEXCEPT
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addDefaultDataLoader(std::unique_ptr<DataLoader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::makeDataLoader(
        const std::string& tag, Args&&... args) NOEXCEPT
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addDataLoader(tag, std::unique_ptr<DataLoader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::makeCustomDataLoader(
        const std::string& name, Args&&... args) NOEXCEPT
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addCustomDataLoader(name, std::unique_ptr<DataLoader>(ptr));
        return *ptr;
    }

    template<typename T>
    void AssetManager<T>::clear() NOEXCEPT
    {
        _assets->clear();
    }

    template<typename T>
    bool AssetManager<T>::remove(const std::string& name) NOEXCEPT
    {
        auto itr = _assets->find(name);
        if(itr != _assets->end())
        {
            _assets->erase(itr);
            return true;
        }
        return false;
    }

    template<typename T>
    bool AssetManager<T>::remove(const std::shared_ptr<T>& asset) NOEXCEPT
    {
        bool found = false;
        for(auto itr = _assets.begin(); itr != _assets.end();)
        {
            if(itr->second == asset)
            {
                _assets->erase(itr++);
                found = true;
            }
            else
            {
                ++itr;
            }
        }
        return found;
    }

    template<typename T>
    typename AssetManager<T>::Loaders AssetManager<T>::getLoaders(
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
        loaders.push_back(_files);
        return loaders;
    }

    template<typename T>
    template<typename... Args>
    T& AssetManager<T>::makePreload(const std::string& name,
        Args&&... args) NOEXCEPT
    {
        auto asset = std::make_shared<T>(std::forward<Args>(args)...);
        return preload(name, asset);
    }

    template<typename T>
    T& AssetManager<T>::preload(const std::string& name,
        const std::shared_ptr<T>& asset) NOEXCEPT
    {
        (*_assets)[name] = asset;
        return *asset;
    }

    template<typename T>
    bool AssetManager<T>::validate(const std::string& name) const NOEXCEPT
    {
        auto itr = _assets->find(name);
        if(itr != _assets->end())
        {
            return true;
        }

        auto loaders = getLoaders(name);
        for(auto& loader : loaders)
        {
            if(loader->validate(name))
            {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    std::future<std::shared_ptr<T>> AssetManager<T>::load(
        const std::string& name, bool cache) NOEXCEPT
    {
        auto itr = _assets->find(name);
        if(itr != _assets->end())
        {
            std::promise<std::shared_ptr<T>> p;
            p.set_value(itr->second);
            return p.get_future();
        }

        auto loaders = getLoaders(name);
        for(auto& loader : loaders)
        {
            if(loader->validate(name))
            {
                return load(loader, name, cache);
            }
        }
        std::promise<std::shared_ptr<T>> p;
        p.set_exception(std::make_exception_ptr(
            Exception("Could not load asset.")));
        return p.get_future();
    }

    template<typename T>
    std::shared_ptr<T> assetLoadAsync(
      const std::shared_ptr<AssetLoader<T>>& loader,
      const std::shared_ptr<typename AssetManager<T>::Assets>& assets,
      const std::string& name)
    {
        auto asset = std::make_shared<T>(loader->load(name));
        if(assets)
        {
            (*assets)[name] = asset;
        }
        return asset;
    }

    template<typename T>
    std::future<std::shared_ptr<T>> AssetManager<T>::load(
        const std::shared_ptr<Loader>& loader,
            const std::string& name, bool cache)
    {
        auto assets = cache?_assets:nullptr;
        return std::async(std::launch::async, &assetLoadAsync<T>,
          loader, assets, name);
    }

}

#endif
