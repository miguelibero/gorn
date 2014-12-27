#ifndef __gorn__PlatformBridge__
#define __gorn__PlatformBridge__

#include <memory>
#include <string>
#include <gorn/render/Image.hpp>

namespace gorn
{
	class PlatformBridge
	{
	public:
	    std::unique_ptr<Data> readFile(const std::string& name);
	    std::unique_ptr<Image> readImage(const std::string& name);
	};
}

#endif /* defined(__gorn__PlatformBridge__) */
