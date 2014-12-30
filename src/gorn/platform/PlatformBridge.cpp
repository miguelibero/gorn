
#include <gorn/platform/PlatformBridge.hpp>

namespace gorn
{
	void PlatformBridge::addImageLoader(std::unique_ptr<ImageLoader> loader)
	{
		_imageLoaders.push_back(std::move(loader));
	}

	std::unique_ptr<Image> PlatformBridge::loadImage(const Data& data)
	{
		for(auto& loader : _imageLoaders)
		{
			if(loader->validate(data))
			{
				return loader->load(data);
			}
		}
		return nullptr;
	}
}
