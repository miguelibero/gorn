#ifndef __gorn__Image__
#define __gorn__Image__

#include <gorn/base/Data.hpp>
#include <gorn/render/Gl.hpp>
#include <gorn/render/Enums.hpp>
#include <glm/glm.hpp>

namespace gorn
{
    enum class ImageFormat
    {
        Uncompressed
    };

	class Image
	{
    public:
        typedef ImageFormat Format;
	private:
		Data _data;
		glm::vec2 _size;
	    bool _hasAlpha;
	    BasicType _type;
	    Format _format;

	public:
		Image(Data&& data, const glm::vec2& size, bool hasAlpha=true,
            BasicType type=BasicType::UnsignedInteger,
            Format format=Format::Uncompressed);
	    const glm::vec2& getSize() const;
        bool hasAlpha() const;
	    BasicType getType() const;
	    Format getFormat() const;
	    const Data& getData() const;
	};
}

#endif
