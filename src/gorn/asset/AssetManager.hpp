#ifndef __gorn__AssetManager__
#define __gorn__AssetManager__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <gorn/asset/AssetLoader.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    template<typename T>
	class AssetManager
	{
    public:
        typedef AssetLoader<T> Loader;
	private:
        std::shared_ptr<FileManager> _fileManager;
		std::vector<std::shared_ptr<Loader>> _loaders;
        std::future<T> load(const std::shared_ptr<Loader>& loader, Data&& data);

	public:
        AssetManager(const std::shared_ptr<FileManager>& fileMng);
	    std::future<T> load(const std::string& tag, const std::string& name);
	    std::future<T> load(const std::string& name);

	    void addLoader(std::unique_ptr<Loader>&& loader);

        template<typename L, typename... Args>
        void addLoader(Args&&... args);
	};

    template<typename T>
	AssetManager<T>::AssetManager(const std::shared_ptr<FileManager>& mng):
    _fileManager(mng)
    {
    }

    template<typename T>
	void AssetManager<T>::addLoader(std::unique_ptr<Loader>&& loader)
	{
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
		_loaders.push_back(std::move(loader));
	}

    template<typename T>
    template<typename L, typename... Args>
    void AssetManager<T>::addLoader(Args&&... args)
    {
        addLoader(std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
	std::future<T> AssetManager<T>::load(const std::string& tag, const std::string& name)
	{
        auto data = _fileManager->load(tag, name).get();
        for(auto& loader : _loaders)
		{
			if(loader->validate(data))
			{
				return load(loader, std::move(data));
			}
		}
		throw Exception("Could not load asset.");
	}

    template<typename T>
    std::future<T> AssetManager<T>::load(const std::shared_ptr<Loader>& loader, Data&& data)
    {
        return std::async(std::launch::async, [loader](Data&& data){
            return loader->load(std::move(data));
        }, std::move(data));
    }

}

#endif
