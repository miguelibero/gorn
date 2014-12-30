#include <gorn/platform/PlatformBridge.hpp>
#include <fstream>


namespace gorn
{
	std::unique_ptr<Data> PlatformBridge::readFile(const std::string& name)
	{
	    std::ifstream stream(name);
		return std::unique_ptr<Data>(new Data(stream));
	}

	std::unique_ptr<Image> PlatformBridge::readImage(const std::string& name)
	{
	    return loadImage(*readFile(name));
	}
}
