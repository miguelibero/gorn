
#include <gorn/platform/StbImageLoader.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/base/Exception.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace gorn
{

    StbImageLoader::StbImageLoader() NOEXCEPT
    {
    }

	bool StbImageLoader::validate(const buffer& input) const NOEXCEPT
    {
        int width;
        int height;
        int comp;
        auto result = stbi_info_from_memory(input.data(), input.size(),
            &width, &height, &comp);
		return result == 1;
    }

	Image StbImageLoader::load(const buffer& input) const
    {
        int width;
        int height;
        int comp;
        auto ptr = stbi_load_from_memory(input.data(),
            input.size(), &width, &height, &comp, 0);

        if(ptr == nullptr)
        {
            throw Exception(stbi_failure_reason());
        }

        bool hasAlpha = comp > 3;
        return Image(buffer(ptr, comp*width*height), Image::DataOrigin::TopLeft,
            glm::vec2(width, height), hasAlpha, BasicType::UnsignedByte);
    }
}
