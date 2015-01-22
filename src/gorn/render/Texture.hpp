#ifndef __gorn__Texture__
#define __gorn__Texture__

#include <gorn/render/Gl.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>

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
        glm::vec2 _size;
	public:
		Texture(GLenum target=GL_TEXTURE_2D);
		~Texture();
		GLuint getId() const;
        void setImage(const Image& img, GLint lodLevel=0);
        void setParameter(GLenum name, GLint value);
        void setParameter(GLenum name, GLfloat value);
        void setParameter(GLenum name, const std::vector<GLint>& value);
        void setParameter(GLenum name, const std::vector<GLfloat>& value);
        void bind();
        void activate(size_t pos);
        const glm::vec2& getSize() const;
        float getScale() const;
	};
}

#endif
