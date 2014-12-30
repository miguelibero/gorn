#ifndef __gorn__PlatformBridge__
#define __gorn__PlatformBridge__

#include <memory>
#include <string>
#include <gorn/render/Image.hpp>
#include <gorn/platform/ImageLoader.hpp>

namespace gorn
{
	class PlatformBridge
	{
	private:
		std::vector<std::unique_ptr<ImageLoader>> _imageLoaders;
	protected:
		std::unique_ptr<Image> loadImage(const Data& data);
	public:
	    std::unique_ptr<Data> readFile(const std::string& name);
	    std::unique_ptr<Image> readImage(const std::string& name);
	    void addImageLoader(std::unique_ptr<ImageLoader> loader);
	};
}

#endif /* defined(__gorn__PlatformBridge__) */
