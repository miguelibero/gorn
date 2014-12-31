#ifndef __gorn__PlatformBridge__
#define __gorn__PlatformBridge__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <map>
#include <gorn/platform/ImageLoader.hpp>
#include <gorn/platform/FileLoader.hpp>

namespace gorn
{
	class PlatformBridge
	{
	private:
		std::vector<std::unique_ptr<ImageLoader>> _imageLoaders;
		std::map<std::string,std::vector<std::unique_ptr<FileLoader>>> _fileLoaders;
	public:
	    std::future<Data> readFile(const std::string& name);
	    std::future<Image> readImage(const std::string& name);
	    void addImageLoader(std::unique_ptr<ImageLoader> loader);
	    void addFileLoader(const std::string& tag, std::unique_ptr<FileLoader> loader);
        void addFileLoader(std::unique_ptr<FileLoader> loader);
	};
}

#endif
