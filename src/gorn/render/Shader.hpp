#ifndef __gorn__Shader__
#define __gorn__Shader__

#include <gorn/base/Data.hpp>
#include <gorn/render/Gl.hpp>

namespace gorn
{
	class Shader
	{
	private:
		GLuint _id;
	public:
		Shader(const Data& source, GLenum type);
		~Shader();
		GLuint getId() const;
	};
}

#endif