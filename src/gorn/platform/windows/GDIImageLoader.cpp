

#include <gorn/platform/windows/GDIImageLoader.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn {

	bool GDIImageLoader::validate(const Data& inputData) const
    {
		return true;
    }


	Image GDIImageLoader::load(Data&& inputData) const
    {
		GLsizei imgWidth = 1;
		GLsizei imgHeight = 1;
		GLenum format = GL_RGBA;
		return Image(Data({1.0f, 0.0f, 0.0f, 1.0f}),
            imgWidth, imgHeight, format, GL_UNSIGNED_BYTE);
    }
}
