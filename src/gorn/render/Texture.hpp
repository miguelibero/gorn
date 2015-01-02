#ifndef __gorn__Texture__
#define __gorn__Texture__

#include <gorn/render/Gl.hpp>
#include <map>

namespace gorn
{
	class Image;

	class Texture
	{
	private:
        static std::map<GLenum, GLuint> s_currentIds;
        static std::map<size_t, GLuint> s_activeIds;
		GLuint _id;
        GLenum _target;
	public:
		Texture(const Image& img, GLenum target=GL_TEXTURE_2D, GLint lodLevel=0);
		~Texture();
		GLuint getId() const;
        void setImage(const Image& img, GLint lodLevel=0);
        void bind();
        void activate(size_t pos);
	};
}

#endif
