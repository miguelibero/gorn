#ifndef __gorn__Texture__
#define __gorn__Texture__

#include <gorn/render/Gl.hpp>

namespace gorn
{
	class Image;

	class Texture
	{
	private:
		GLuint _id;

	public:
		Texture(const Image& img);
		~Texture();
		GLuint getId() const;
	};
}

#endif