#ifndef __gorn__FileAssetLoader__
#define __gorn__FileAssetLoader__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <map>
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
		std::map<std::string, Loaders> _loaders;

        Loaders getLoaders(const std::string& name) const NOEXCEPT;

	public:
        FileAssetLoader(FileManager& files) NOEXCEPT;

        virtual bool validate(const std::string& name) const NOEXCEPT;
        virtual T load(const std::string& name) const;

	    void addDefaultLoader(std::unique_ptr<Loader>&& loader) NOEXCEPT;
        void addLoader(const std::string& tag,
            std::unique_ptr<Loader>&& loader) NOEXCEPT;

        template<typename L, typename... Args>
        void addDefaultLoader(Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        void addLoader(const std::string& tag, Args&&... args) NOEXCEPT;
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
        addLoader(String::kDefaultTag, std::move(loader));
    }

    template<typename T>
    void FileAssetLoader<T>::addLoader(const std::string& tag,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
	{
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
		_loaders[tag].push_back(std::move(loader));
	}

    template<typename T>
    template<typename L, typename... Args>
    void FileAssetLoader<T>::addDefaultLoader(Args&&... args) NOEXCEPT
    {
        addDefaultLoader(std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
    template<typename L, typename... Args>
    void FileAssetLoader<T>::addLoader(const std::string& tag,
        Args&&... args) NOEXCEPT
    {
        addLoader(tag, std::unique_ptr<Loader>(
            new L(std::forward<Args>(args)...)));
    }

    template<typename T>
    typename FileAssetLoader<T>::Loaders FileAssetLoader<T>::getLoaders(
        const std::string& name) const NOEXCEPT
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
        return loaders;
    }

    template<typename T>
    bool FileAssetLoader<T>::validate(const std::string& name) const NOEXCEPT
    {
        auto loaders = getLoaders(name);
        auto data = _files.load(name).get();
        for(auto& loader : loaders)
	    {
		    if(loader->validate(data))
		    {
			    return true;
		    }
	    }
        return false;
    }

    template<typename T>
    T FileAssetLoader<T>::load(const std::string& name) const
    {
        auto loaders = getLoaders(name);
        auto data = _files.load(name).get();
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
