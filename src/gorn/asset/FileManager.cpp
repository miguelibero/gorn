
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/FileLoader.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#include <algorithm>

namespace gorn
{
    const char* FileManager::kDefaultTag = "default";
    const char* FileManager::kTagSeparator = ":";

	void FileManager::addLoader(const std::string& tag, std::unique_ptr<Loader>&& loader)
	{
        if(loader == nullptr)
        {
            throw Exception("Cannot add an empty loader");
        }
		_loaders[tag].push_back(std::move(loader));
	}

    void FileManager::addLoader(std::unique_ptr<Loader>&& loader)
    {
        addLoader(kDefaultTag, std::move(loader));
    }

	std::future<Data> FileManager::load(const std::string& aname, bool cache)
	{
        {
            auto itr = _preloads.find(aname);
            if(itr != _preloads.end())
            {
                std::promise<Data> p;
                p.set_value(itr->second);
                return p.get_future();
            }
        }

        auto parts = String::split(aname, kTagSeparator);
        std::string name(aname);
        std::string tag(kDefaultTag);        
        if(parts.size() > 1)
        {
            tag = parts.front();
            name = parts.back();
        }

        std::vector<std::shared_ptr<Loader>> loaders;
        if(tag != kDefaultTag)
        {
            auto itr = _loaders.find(tag);
            if(itr != _loaders.end())
            {
                for(auto& loader : itr->second)
                {
                    loaders.push_back(loader);
                }
            }
        }
        {
            auto itr = _loaders.find(kDefaultTag);
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
            if(loader->validate(name))
            {
                return load(loader, name);
            }
        }
       
		throw Exception(std::string("Could not load file '")+name+"' with tag '"+tag+"'.");
	}

    std::future<Data> FileManager::load(const std::shared_ptr<Loader>& loader, const std::string& name)
    {
        return std::async(std::launch::async, [loader](const std::string& name){
            return loader->load(name);
        }, name);
    }

    void FileManager::preload(const std::string& name, Data&& data)
    {
        _preloads[name] = std::move(data);
    }

    bool FileManager::prefix(std::string& name, const std::string& prefix)
    {
        return String::prefix(name, prefix, kTagSeparator);
    }
}
