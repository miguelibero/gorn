#ifndef __gorn__BlendMode__
#define __gorn__BlendMode__

#include <gorn/gl/Enums.hpp>
namespace gorn
{
    class BlendMode
    {
	private:
		BlendFactor _src;
		BlendFactor _dst;
	public:
		BlendMode();
		BlendMode(const BlendMode& other);
		BlendMode(BlendFactor src, BlendFactor dst);
		bool operator==(const BlendMode& other) const;
		bool operator!=(const BlendMode& other) const;
		bool enabled() const;
		void apply(const BlendMode& old);
		void apply();
    };
}

#endif

