#ifndef __gorn__Image__
#define __gorn__Image__

#include <gorn/base/Data.hpp>
#include <gorn/render/Gl.hpp>

namespace gorn
{
	class Image
	{
	private:
		Data _data;
		GLsizei _width;
	    GLsizei _height;
	    GLenum _format;
	    GLenum _type;
	    GLint _border;
	    GLint _internalFormat;

	public:
		Image(Data&& data, GLsizei w, GLsizei h, GLenum format, GLenum type, GLint border=0, GLint internalFormat=0);
	    GLint getInternalFormat() const;
	    GLsizei getWidth() const;
	    GLsizei getHeight() const;
	    GLint getBorder() const;
	    GLenum getFormat() const;
	    GLenum getType() const;
	    const Data& getData() const;
	};
}

#endif
