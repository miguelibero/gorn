#ifndef __gorn__Image__
#define __gorn__Image__

#include <gorn/base/Data.hpp>
#include <gorn/base/Config.hpp>
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
            Format format=Format::Uncompressed) NOEXCEPT;
	    const glm::vec2& getSize() const NOEXCEPT;
        bool hasAlpha() const NOEXCEPT;
	    BasicType getType() const NOEXCEPT;
	    Format getFormat() const NOEXCEPT;
	    const Data& getData() const NOEXCEPT;
	};
}

#endif
