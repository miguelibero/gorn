
#include <gorn/platform/windows/SOILImageLoader.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/base/Exception.hpp>
#include <SOIL2/SOIL2.h>


namespace gorn {

	bool SOILImageLoader::validate(const buffer& inputData) const
    {
		return true;
    }
	Image SOILImageLoader::load(const buffer& inputData) const
    {
		int width;
		int height;
		int channels;
		unsigned char* data = SOIL_load_image_from_memory(
			inputData.data(),
			inputData.size(),
			&width, &height, &channels,
			SOIL_LOAD_AUTO);

        bool hasAlpha = false;
		switch (channels)
		{
		case 3:
			hasAlpha = false;
			break;
		case 4:
			hasAlpha = true;
			break;
		default:
			throw Exception("Invalid amount of image channels");
			break;
		}
		return Image(buffer(data, width*height*channels*sizeof(unsigned char)),
			glm::vec2(width, height), hasAlpha, BasicType::UnsignedByte);
    }
}
