
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/base/Data.hpp>

namespace gorn
{
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
        addFileLoader("", std::move(loader));
    }

	std::future<Data> PlatformBridge::readFile(const std::string& name)
	{
        std::string tag;
        std::string fname;
        size_t p = name.find(":");
        if(p != std::string::npos)
        {
            tag = name.substr(0, p);
            fname = name.substr(p+1);
        }
        for(auto itr = _fileLoaders.begin(); itr != _fileLoaders.end(); ++itr)
        {
            if(itr->first == tag || itr->first.empty())
            {
                for(auto& loader : itr->second)
                {
                    if(loader->validate(fname))
                    {
                        return loader->load(fname);
                    }
                }
            }
        }
       
		throw Exception(std::string("Could not load file '")+name+"'.");
	}

	std::future<Image> PlatformBridge::readImage(const std::string& name)
	{
        auto data = readFile(name).get();
        for(auto& loader : _imageLoaders)
		{
			if(loader->validate(data))
			{
				return loader->load(std::move(data));
			}
		}
		throw Exception("Could not load image.");
	}
}
