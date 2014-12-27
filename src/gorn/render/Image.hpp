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
		GLenum _target;
	    GLint _level;
	    GLint _internalFormat;
	    GLsizei _width;
	    GLsizei _height;
	    GLint _border;
	    GLenum _format;
	    GLenum _type;

	public:
		Image(Data&& data, GLenum target, GLint level, GLint internalFormat,
			GLsizei w, GLsizei h, GLint border, GLenum format, GLenum type);
		GLenum getTarget() const;
	    GLint getLevel() const;
	    GLint getInternalFormat() const;
	    GLsizei getWidth() const;
	    GLsizei getHeight() const;
	    GLint getBorder() const;
	    GLenum getFormat() const;
	    GLenum getType() const;
	    const GLvoid* getData() const;
	};
}

#endif