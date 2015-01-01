#ifndef __gorn__Shader__
#define __gorn__Shader__

#include <gorn/base/Data.hpp>
#include <gorn/render/Gl.hpp>

namespace gorn
{
    enum class ShaderType
    {
        Vertex,
        Fragment
    };

	class Shader
	{
	private:
		GLuint _id;
	public:
        typedef ShaderType Type;

		Shader(const Data& source, ShaderType type);
		~Shader();
		GLuint getId() const;
	};
}

#endif
