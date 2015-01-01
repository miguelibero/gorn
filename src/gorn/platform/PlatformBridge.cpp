
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#include <algorithm>

namespace gorn
{
    const char* PlatformBridge::kDefaultTag = "default";
    const char* PlatformBridge::kTagSeparator = ":";

	void PlatformBridge::addImageLoader(std::unique_ptr<ImageLoader> loader)
	{
		_imageLoaders.push_back(std::move(loader));
	}

	void PlatformBridge::addFileLoader(const std::string& tag, std::unique_ptr<FileLoader> loader)
	{
		_fileLoaders[tag].push_back(std::move(loader));
	}

    void PlatformBridge::addFileLoader(std::unique_ptr<FileLoader> loader)
    {
        addFileLoader(kDefaultTag, std::move(loader));
    }

	std::future<Data> PlatformBridge::readFile(const std::string& atag, const std::string& aname)
	{
        auto parts = String::split(aname, kTagSeparator);
        std::string tag(atag);
        std::string name(aname);
        if(parts.size() > 1)
        {
            tag = parts.front();
            name = parts.back();
        }

        std::vector<FileLoader*> loaders;
        if(tag != kDefaultTag)
        {
            auto itr = _fileLoaders.find(tag);
            if(itr != _fileLoaders.end())
            {
                for(auto& loader : itr->second)
                {
                    loaders.push_back(loader.get());
                }
            }
        }
        auto itr = _fileLoaders.find(kDefaultTag);
        if(itr != _fileLoaders.end())
        {
            for(auto& loader : itr->second)
            {
                loaders.push_back(loader.get());
            }
        }
        for(auto& loader : loaders)
        {
            if(loader->validate(name))
            {
                return loader->load(name);
            }
        }
       
		throw Exception(std::string("Could not load file '")+name+"' with tag '"+tag+"'.");
	}

	std::future<Image> PlatformBridge::readImage(const std::string& tag, const std::string& name)
	{
        auto data = readFile(tag, name).get();
        for(auto& loader : _imageLoaders)
		{
			if(loader->validate(data))
			{
				return loader->load(std::move(data));
			}
		}
		throw Exception("Could not load image.");
	}

    std::future<Data> PlatformBridge::readFile(const std::string& name)
    {
        return readFile(kDefaultTag, name);
    }

    std::future<Image> PlatformBridge::readImage(const std::string& name)
    {
        return readImage(kDefaultTag, name);
    }
}
