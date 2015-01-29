#ifndef __gorn__AssetManager__
#define __gorn__AssetManager__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <map>
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
        typedef std::map<std::string, std::shared_ptr<T>> Assets;
	private:
        std::shared_ptr<FileLoader> _files;
		std::map<std::string, Loaders> _loaders;
		std::shared_ptr<Assets> _assets;

        Loaders getLoaders(const std::string& name) const;

        std::future<std::shared_ptr<T>> load(
            const std::shared_ptr<Loader>& loader,
            const std::string& name, bool cache);

	public:
        AssetManager(FileManager& files);
	    std::future<std::shared_ptr<T>> load(
            const std::string& name, bool cache=false);

        template<typename... Args>
        T& preload(const std::string& name, Args&&... args);

	    void addDefaultLoader(std::unique_ptr<Loader>&& loader);
        void addLoader(const std::string& tag,
            std::unique_ptr<Loader>&& loader);

        template<typename L, typename... Args>
        L& addDefaultLoader(Args&&... args);
        template<typename L, typename... Args>
        L& addLoader(const std::string& tag, Args&&... args);

	    void addDefaultDataLoader(std::unique_ptr<DataLoader>&& loader);
        void addDataLoader(const std::string& tag,
            std::unique_ptr<DataLoader>&& loader);

        template<typename L, typename... Args>
        L& addDefaultDataLoader(Args&&... args);
        template<typename L, typename... Args>
        L& addDataLoader(const std::string& tag, Args&&... args);

        bool remove(const std::shared_ptr<T>& asset);
        bool remove(const std::string& name);
        void clear();
	};

    template<typename T>
	AssetManager<T>::AssetManager(FileManager& files):
    _files(std::make_shared<FileLoader>(files)),
    _assets(std::make_shared<Assets>())
    {
    }

    template<typename T>
	void AssetManager<T>::addDefaultLoader(
        std::unique_ptr<Loader>&& loader)
    {
        addLoader(String::kDefaultTag, std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addLoader(const std::string& tag,
        std::unique_ptr<Loader>&& loader)
	{
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
		_loaders[tag].push_back(std::move(loader));
	}

    template<typename T>
	void AssetManager<T>::addDefaultDataLoader(
        std::unique_ptr<DataLoader>&& loader)
    {
        addDataLoader(String::kDefaultTag, std::move(loader));
    }

    template<typename T>
    void AssetManager<T>::addDataLoader(const std::string& tag,
        std::unique_ptr<DataLoader>&& loader)
	{
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
		_files->addLoader(tag, std::move(loader));
	}

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::addDefaultLoader(Args&&... args)
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addDefaultLoader(std::unique_ptr<Loader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::addLoader(const std::string& tag, Args&&... args)
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addLoader(tag, std::unique_ptr<Loader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::addDefaultDataLoader(Args&&... args)
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addDefaultDataLoader(std::unique_ptr<DataLoader>(ptr));
        return *ptr;
    }

    template<typename T>
    template<typename L, typename... Args>
    L& AssetManager<T>::addDataLoader(const std::string& tag, Args&&... args)
    {
        auto ptr = new L(std::forward<Args>(args)...);
        addDataLoader(tag, std::unique_ptr<DataLoader>(ptr));
        return *ptr;
    }

    template<typename T>
	void AssetManager<T>::clear()
    {
        _assets->clear();
    }

    template<typename T>
	bool AssetManager<T>::remove(const std::string& name)
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
	bool AssetManager<T>::remove(const std::shared_ptr<T>& asset)
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
        const std::string& name) const
    {
        auto parts = String::splitTag(name);
        auto itr = _loaders.find(parts.first);
        Loaders loaders;
        if(itr != _loaders.end())
        {
            for(auto& loader : itr->second)
            {
                loaders.push_back(loader);
            }
        }
        if(parts.first != String::kDefaultTag)
        {
            itr = _loaders.find(String::kDefaultTag);
            if(itr != _loaders.end())
            {
                for(auto& loader : itr->second)
                {
                    loaders.push_back(loader);
                }
            }
        }
        loaders.push_back(_files);
        return loaders;
    }

    template<typename T>
    template<typename... Args>
    T& AssetManager<T>::preload(const std::string& name, Args&&... args)
    {
        auto asset = std::make_shared<T>(std::forward<Args>(args)...);
        (*_assets)[name] = asset;
        return *asset;
    }

    template<typename T>
	std::future<std::shared_ptr<T>> AssetManager<T>::load(
        const std::string& name, bool cache)
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
		throw Exception("Could not load asset.");
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
