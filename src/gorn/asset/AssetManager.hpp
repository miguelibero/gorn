#ifndef __gorn__AssetManager__
#define __gorn__AssetManager__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <map>
#include <gorn/asset/AssetLoader.hpp>
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
        typedef std::vector<std::shared_ptr<Loader>> Loaders;
        typedef std::map<std::string, std::shared_ptr<T>> Assets;
	private:
        FileManager& _files;
		std::map<std::string, Loaders> _loaders;
		std::shared_ptr<Assets> _assets;
        std::future<std::shared_ptr<T>> load(
            const std::shared_ptr<Loader>& loader,
            Data&& data, const std::string& name, bool cache);
        std::future<std::shared_ptr<T>> load(
            Data&& data, const std::string& name, bool cache);

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
        void addDefaultLoader(Args&&... args);
        template<typename L, typename... Args>
        void addLoader(const std::string& tag, Args&&... args);

        bool remove(const std::shared_ptr<T>& asset);
        bool remove(const std::string& name);
        void clear();
	};

    template<typename T>
	AssetManager<T>::AssetManager(FileManager& files):
    _files(files), _assets(std::make_shared<Assets>())
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
    template<typename L, typename... Args>
    void AssetManager<T>::addDefaultLoader(Args&&... args)
    {
        addDefaultLoader(std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
    template<typename L, typename... Args>
    void AssetManager<T>::addLoader(const std::string& tag, Args&&... args)
    {
        addLoader(tag, std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
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
        auto data = _files.load(name).get();
        return load(std::move(data), name, cache);
	}

    template<typename T>
    std::future<std::shared_ptr<T>> AssetManager<T>::load(
        Data&& data, const std::string& name, bool cache)
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
        for(auto& loader : loaders)
	    {
		    if(loader->validate(data))
		    {
			    return load(loader, std::move(data), name, cache);
		    }
	    }
		throw Exception("Could not load asset.");
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
    std::shared_ptr<T> assetLoadAsync(Data&& data,
      const std::shared_ptr<AssetLoader<T>>& loader,
      const std::shared_ptr<typename AssetManager<T>::Assets>& assets,
      const std::string& name)
    {
        auto asset = std::make_shared<T>(loader->load(std::move(data)));
        if(assets)
        {
            (*assets)[name] = asset;
        }
        return asset;
    }

    template<typename T>
    std::future<std::shared_ptr<T>> AssetManager<T>::load(
        const std::shared_ptr<Loader>& loader,
        Data&& data, const std::string& name, bool cache)
    {
        auto assets = cache?_assets:nullptr;
        return std::async(std::launch::async, &assetLoadAsync<T>,
          std::move(data), loader, assets, name);
    }

}

#endif
