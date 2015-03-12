
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/FileLoader.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>
#include <gorn/base/String.hpp>
#include <algorithm>

namespace gorn
{

	void FileManager::addLoader(const std::string& tag,
        std::unique_ptr<Loader>&& loader) NOEXCEPT
	{
        if(loader != nullptr)
        {
    		_loaders[tag].push_back(std::move(loader));
        }
	}

    void FileManager::addLoader(std::unique_ptr<Loader>&& loader) NOEXCEPT
    {
        addLoader(String::kDefaultTag, std::move(loader));
    }

    std::vector<std::shared_ptr<FileManager::Loader>> FileManager::getLoaders(
        const std::pair<std::string,std::string>& parts) const NOEXCEPT
    {
        std::vector<std::shared_ptr<Loader>> loaders;
        if(parts.first != String::kDefaultTag)
        {
            auto itr = _loaders.find(parts.first);
            if(itr != _loaders.end())
            {
                for(auto& loader : itr->second)
                {
                    loaders.push_back(loader);
                }
            }
        }
        {
            auto itr = _loaders.find(String::kDefaultTag);
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

    bool FileManager::validate(const std::string& name) const NOEXCEPT
    {
        auto itr = _preloads.find(name);
        if(itr != _preloads.end())
        {
            return true;
        }

        auto parts = String::splitTag(name);
        auto loaders = getLoaders(parts);
        for(auto& loader : loaders)
        {
            if(loader->validate(parts.second))
            {
                return true;
            }
        }
        return false;
    }

	std::future<buffer> FileManager::load(const std::string& name, bool cache)
	{
        auto itr = _preloads.find(name);
        if(itr != _preloads.end())
        {
            std::promise<buffer> p;
            p.set_value(itr->second);
            return p.get_future();
        }

        auto parts = String::splitTag(name);
        auto loaders = getLoaders(parts);
        for(auto& loader : loaders)
        {
            if(loader->validate(parts.second))
            {
                return load(loader, parts.second);
            }
        }
       
		throw Exception(std::string("Could not load file '")
            +parts.second+"' with tag '"+parts.first+"'.");
	}

    std::future<buffer> FileManager::load(
      const std::shared_ptr<Loader>& loader, const std::string& name)
    {
        return std::async(std::launch::async, [loader](const std::string& name){
            return loader->load(name);
        }, name);
    }

    void FileManager::preload(const std::string& name, buffer&& data) NOEXCEPT
    {
        _preloads[name] = std::move(data);
    }

}
